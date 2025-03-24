#include "icmp_proto.hpp"
#include <netinet/in.h>
#include <sys/socket.h>
#include <chrono>
// Przypomnienie
// argc == ilość argumentów na wejściu w tym nazwa pliku binarnego
// argv == argumenty, argv[0] == nazwa pliku binarnego
//

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
        sender.set_header();

        // std::cout << IP_adress << std::endl;

        for (int ttl = 1; ttl <= 30; ttl++) {
            setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));
            std::cout << "TLL = " << ttl << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 3; i++) {
                sender.sent_to_recipinet(sockfd);
            }
            receiver.receive_packets(sockfd);
            auto end = std::chrono::high_resolution_clock::now();
            int rtt = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "time: " << rtt << std::endl;
        }

    } catch (const std::runtime_error& e) {
        std::cerr << "Error " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
