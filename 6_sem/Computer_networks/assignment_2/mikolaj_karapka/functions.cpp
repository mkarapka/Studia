//Mikołaj Krapka
//339286

#include "functions.hpp"
#include <unistd.h>

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

void moving_window(struct sockaddr_in &server_address, int &sockfd,
                   std::string FILE_NAME, size_t FILE_SIZE,
                   int SWS, size_t max_dgram_size) {

    const size_t num_fragments = (FILE_SIZE + max_dgram_size - 1) / max_dgram_size;
    std::vector<PacketFragment> fragments(num_fragments);

    for (size_t i = 0; i < num_fragments; ++i) {
        fragments[i] = {
            .start = i * max_dgram_size,
            .length = std::min(max_dgram_size, FILE_SIZE - i * max_dgram_size),
            .received = false,
            .last_sent = std::chrono::steady_clock::now() - std::chrono::milliseconds(10)
        };
    }

    std::map<size_t, std::vector<u_int8_t>> window_buffer;
    size_t base = 0;
    u_int8_t buffer[1500];
    size_t sum_of_len = 0;

    std::ofstream file(FILE_NAME, std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file: " + FILE_NAME);

    while (base < num_fragments) {
        auto now = std::chrono::steady_clock::now();

        for (size_t i = base; i < std::min(base + SWS, num_fragments); ++i) {
            auto &frag = fragments[i];
            if (frag.received) continue;

            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - frag.last_sent).count() >= 100) {
                std::string request = "GET " + std::to_string(frag.start) + " " + std::to_string(frag.length) + "\n";
                memcpy(buffer, request.c_str(), request.length());
                size_t len = request.length();
                sent_to_server(server_address, buffer, len, sockfd);
                frag.last_sent = now;
            }
        }

        ssize_t bytes_read = receive_packet(sockfd, buffer, sizeof(buffer), server_address, 100);
        if (bytes_read > 0) {
            size_t rec_start, rec_length;
            u_int8_t* data_ptr = nullptr;

            if (parse_data_response(buffer, bytes_read, rec_start, rec_length, &data_ptr)) {
                size_t index = rec_start / max_dgram_size;
                if (index < base || index >= base + SWS || fragments[index].received)
                    continue;

                window_buffer[index] = std::vector<u_int8_t>(data_ptr, data_ptr + rec_length);
                fragments[index].received = true;
            }
        }

        while (base < num_fragments && fragments[base].received) {
            file.write(reinterpret_cast<char*>(window_buffer[base].data()), fragments[base].length);
            if (!file)
                throw std::runtime_error("Failed to write to file at base fragment " + std::to_string(base));

            sum_of_len += fragments[base].length;
            std::cout << ((float)sum_of_len / (float)FILE_SIZE) * 100.0f << "% done" << std::endl;

            window_buffer.erase(base);
            ++base;
        }
    }

    file.close();
    if (!file)
        throw std::runtime_error("Failed to close file: " + FILE_NAME);
}
