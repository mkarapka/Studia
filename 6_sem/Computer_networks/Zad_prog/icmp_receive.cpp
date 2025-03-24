#include "icmp_proto.hpp"
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/poll.h>
#include<numeric>

namespace icmp_prot {
void Receiver::receive_packets(int& sockfd) {
    int TIMEOUT = 1000;
    struct pollfd ps;
    ps.fd = sockfd;
    ps.events = POLLIN;
    ps.revents = 0;

    int received_count = 0;
    std::vector<std::string> responding_ips;
    std::vector<int> response_times;

    while (received_count < 3) {
        int ready = poll(&ps, 1, TIMEOUT);
        if (ready > 0) {
            if (ps.revents & POLLIN) {
                auto recv_start = std::chrono::high_resolution_clock::now();
                size_t packet_len =
                    recvfrom(sockfd,
                        buffer,
                        IP_MAXPACKET,
                        0,
                        (struct sockaddr*)&sender,
                        &sender_len);
                auto recv_end = std::chrono::high_resolution_clock::now();

                if (packet_len > 0) {
                    char ip_str[20];
                    inet_ntop(AF_INET, &(sender.sin_addr), ip_str,
                              sizeof(ip_str));

                    int rtt =
                        std::chrono::duration_cast<std::chrono::milliseconds>(
                            recv_end - recv_start)
                            .count();
                        response_times.push_back(rtt);
                        responding_ips.push_back(ip_str);

                    // std::cout << "IP packet with ICMP content from: " << ip_str
                    //           << " time: " << rtt << std::endl;

                    struct ip* ip_header = (struct ip*)buffer;
                    u_int8_t* icmp_packet = buffer + 4 * ip_header->ip_hl;
                    struct icmp* icmp_header = (struct icmp*)icmp_packet;

                    if (icmp_header->icmp_type == ICMP_ECHOREPLY) {
                        std::cout << responding_ips[0] << " " << rtt << "ms" << std::endl;
                        exit(EXIT_SUCCESS);
                    }
                    received_count++;

                } else {
                    std::cerr << "Error receiving packet" << std::endl;
                }
            }
        } else {
            break;
        }
    }
    if (received_count < 3){
        std::cout << "*" << std::endl;
    } else{
        for(const auto& ip : responding_ips){
            std::cout << ip << " ";
        }
        if (response_times.size() < 3){
            std::cout << "???" << std::endl;
        } else{
            int rtt_avg = std::accumulate(response_times.begin(), response_times.end(), 0) / response_times.size();
            std::cout << rtt_avg << "ms" << std::endl;
        }
    }

}
} // namespace icmp_prot
