#include "functions.hpp"
#include <cmath>
int main(int argc, char* argv[]){

    try {
        if(argc != 5){
            throw std::runtime_error("Improper number of arguments");
        }
        const char* IP_ADRESS = argv[1];
        u_int16_t PORT = conver_str_to_uint16(argv[2]);
        std::string FILE_NAME = argv[3];
        size_t FILE_SIZE = conver_str_to_size_t(argv[4]);

        int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

        struct sockaddr_in server_address = {};
        set_server_address(server_address, PORT, IP_ADRESS);

        {
            std::ofstream clear_file(FILE_NAME, std::ios::trunc);
        }

        u_int8_t buffer[1024];
        std::vector<pair_size_t> dgrams_info = divide_into_dgram(FILE_SIZE);

        size_t i = 0;
        while(i < dgrams_info.size()){
            pair_size_t pair = dgrams_info[i];
            std::string request = "GET " +
                    std::to_string(pair.start) + " " +
                    std::to_string(pair.length) + "\n";

            size_t request_len = request.length();
            memcpy(buffer, request.c_str(), request_len);
            sent_to_server(server_address, buffer, request_len, sockfd);
            ssize_t bytes_read = receive_packet(sockfd, buffer, sizeof(buffer), server_address, 1000);

            if(bytes_read > 0){
                u_int8_t* data_ptr = nullptr;
                size_t rec_start, rec_length;
                if(parse_data_response(buffer, bytes_read, rec_start, rec_length, &data_ptr) &&
                    pair.start == rec_start && pair.length == rec_length){
                    std::ofstream file(FILE_NAME, std::ios::app | std::ios::binary);
                    file.write(reinterpret_cast<const char*>(data_ptr), pair.length);

                    std::cout  << ((float)pair.start / (float)FILE_SIZE) * 100.0  << "% done" << std::endl;
                    file.close();
                    i++;
                }
            }
        }
        std::cout  << "100% done" << std::endl;



        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Unknown error occurred" << std::endl;
        }
    }
