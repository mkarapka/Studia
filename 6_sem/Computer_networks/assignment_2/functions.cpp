

#include "functions.hpp"
#include <cstddef>
#include <cstdint>
#include <deque>
#include <future>

// other functions
u_int16_t conver_str_to_uint16(const char *str) {
    long value = strtol(str, NULL, 10);
    if (value < 0 || value > UINT16_MAX)
        throw std::runtime_error("Value out of range for uint16");
    return static_cast<u_int16_t>(value);
}

size_t conver_str_to_size_t(const char *str) {
    unsigned long long value = strtoull(str, NULL, 10);
    if (value > SIZE_MAX)
        throw std::runtime_error("Value out of range for size_t");
    return static_cast<size_t>(value);
}

void set_server_address(struct sockaddr_in &server_address, u_int16_t &PORT,
                        const char *IP_ADDRESS) {
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    inet_pton(AF_INET, IP_ADDRESS, &server_address.sin_addr);
}
// Send funtions
ssize_t sent_to_server(struct sockaddr_in &server, u_int8_t *buffer,
                       size_t &buffer_size, int &sockfd) {
    ssize_t bytes_sent = sendto(
        sockfd,
        buffer,
        buffer_size,
        0,
        (struct sockaddr *)&server,
        sizeof(server)
    );
    return bytes_sent;
}

// To fix, later we will want to sent without pre computing vector array
std::vector<pair_size_t> divide_into_dgram(size_t FILE_SIZE,
                                           size_t max_dgram_size) {
    std::vector<pair_size_t> dgrams_info;
    size_t dgram_len = max_dgram_size, index = 0;
    while (FILE_SIZE > 0) {
        dgram_len = std::min(max_dgram_size, FILE_SIZE);
        dgrams_info.push_back({index, dgram_len});
        index += dgram_len;
        FILE_SIZE -= dgram_len;
    }
    return dgrams_info;
}

// receive functions
ssize_t receive_packet(int sockfd, u_int8_t *buffer, size_t buffer_size,
                       struct sockaddr_in &server_addr, int timeout_ms) {
    struct pollfd ps;
    ps.fd = sockfd;
    ps.events = POLLIN;
    ps.revents = 0;

    int ready = poll(&ps, 1, timeout_ms);

    if (ready > 0) {
        struct sockaddr_in sender_addr;
        socklen_t sender_len = sizeof(sender_addr);

        ssize_t bytes_read = recvfrom(
            sockfd,
            buffer,
            buffer_size,
            0,
            (struct sockaddr *)&sender_addr,
            &sender_len
        );

        if (bytes_read < 0) {
        throw std::runtime_error("recvfrom failed: " +
                                std::string(strerror(errno)));
        }

        if (sender_addr.sin_addr.s_addr != server_addr.sin_addr.s_addr) {
        std::cerr << "Received packet from unexpected source, ignoring"
                    << std::endl;
        return 0;
        }

        return bytes_read;
    } else if (ready == 0) {
        return 0;
    } else {
        throw std::runtime_error("Poll error: " + std::string(strerror(errno)));
    }
}

// Parssing function
bool parse_data_response(u_int8_t *buffer, ssize_t bytes_read, size_t &start,
                         size_t &length, u_int8_t **data_ptr) {
    std::string header(reinterpret_cast<char *>(buffer), bytes_read);

    size_t newline_pos = header.find('\n');
    if (newline_pos == std::string::npos) {
        return false;
    }
    std::string header_only = header.substr(0, newline_pos);
    if (header_only.substr(0, 5) != "DATA ") {
        return false;
    }

    if (sscanf(header_only.c_str(), "DATA %zu %zu", &start, &length) != 2) {
        return false;
    }

    *data_ptr = buffer + newline_pos + 1;
    return true;
}

void window_element::sent_elem(struct sockaddr_in &server_address, int &sockfd) {
    std::string request = "GET " + std::to_string(dgram_info.start) + " " +
                            std::to_string(dgram_info.length) + "\n";

    size_t request_len = request.length();
    memcpy(buffer, request.c_str(), request_len);
    sent_to_server(server_address, buffer, request_len, sockfd);
}

bool window_element::receive_elem(struct sockaddr_in &server_address, int &sockfd) {
    ssize_t bytes_read = receive_packet(
        sockfd,
        buffer,
        sizeof(buffer),
        server_address,
        2
    );
    size_t rec_start, rec_length;

    return bytes_read > 0 &&
            parse_data_response(buffer, bytes_read, rec_start, rec_length,
                                &data_ptr) &&
            dgram_info.start == rec_start && dgram_info.length == rec_length;
}


void write_into_file(std::string FILE_NAME, u_int8_t **data_ptr, size_t length){
    std::ofstream file(FILE_NAME, std::ios::app | std::ios::binary);
    file.write(reinterpret_cast<const char*>(data_ptr), length);
    file.close();
}

void moving_window(struct sockaddr_in &server_address, int &sockfd,
                    std::string FILE_NAME, size_t FILE_SIZE,
                    int SWS, size_t max_dgram_size){
    size_t n = FILE_SIZE;
    std::deque<window_element> window;
    size_t current_start = 0;
    std::future<void> fut;

    size_t current_len = std::min(n, max_dgram_size);
    current_start += current_len;
    n -= current_len;
    window.push_back({pair_size_t(current_start, current_len), server_address, sockfd});

    while(n > 0 && !window.empty()){
        while((int)window.size() < SWS && n > 0){
            size_t current_len = std::min(n, max_dgram_size);
            current_start += current_len;
            n -= current_len;

            window.push_back({
                pair_size_t(current_start, current_len),
                server_address,
                sockfd}
            );
        }

        window.front().LAR = true;

        for(auto &element : window){
            if(element.received){
                if(element.LAR){
                    write_into_file(
                        FILE_NAME, &element.data_ptr, element.dgram_info.length
                    );
                    std::cout << ((float)element.dgram_info.start / (float)FILE_SIZE) * 100.0
                    << "% done" << std::endl;
                    window.pop_front();
                }
            }
            else{
                fut = std::async(std::launch::async, [&]{
                    element.sent_elem(server_address, sockfd);
                    element.received = element.receive_elem(server_address, sockfd);
                    // future_active = true;
                });
                // element.sent_elem(server_address, sockfd);
                // element.received = element.receive_elem(server_address, sockfd);
            }
        }
    }
    std::cout  << "100% done" << std::endl;
}
