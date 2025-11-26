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

        int SWS = 10, max_datagram_length = 1000;
        moving_window(
            server_address,
            sockfd,
            FILE_NAME,
            FILE_SIZE,
            SWS,
            max_datagram_length);

        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Unknown error occurred" << std::endl;
        }
    }
