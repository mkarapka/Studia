// Mikołaj Karapka
// 339286

#include "icmp_proto.hpp"
#include <netinet/in.h>

int main(int argc, char* argv[]) {
    try {
        if (argc <= 1) {
            throw std::runtime_error("IP adress not provided");
        } else if (argc > 2) {
            throw std::runtime_error("Too many arguments");
        }

        int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
        icmp_prot::Receiver receiver;
        icmp_prot::Sender sender;

        const char* IP_adress = argv[1];
        sender.set_recipinet(IP_adress);


        for (int ttl = 1; ttl <= 30; ttl++) {
            setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));

            auto recv_start = std::chrono::high_resolution_clock::now();
            for (int j = 0; j < 3; j++) {
                sender.set_header(ttl, j);
                sender.sent_to_recipinet(sockfd);
            }
            receiver.receive_packets(sockfd, recv_start, ttl);
        }

    } catch (const std::runtime_error& e) {
        std::cerr << "Error " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
