// Mikołaj Karapka
// 339286

#include "icmp_proto.hpp"
#include <cstddef>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <numeric>
#include <unistd.h>

bool icmp_time_exceeded_verify(struct icmp* icmp_header, int& ttl) {
    if (icmp_header->icmp_type == ICMP_TIME_EXCEEDED) {
        struct ip* inner_ip = (struct ip*)&icmp_header->icmp_data;
        u_int8_t* inner_icmp = (u_int8_t*)inner_ip + 4 * inner_ip->ip_hl;
        struct icmp* inner_icmp_header = (struct icmp*)inner_icmp;

        return inner_icmp_header->icmp_id == getpid() &&
               inner_icmp_header->icmp_seq / 10 == ttl;
    }
    return false;
}

bool icmp_echo_reply_verify(struct icmp* icmp_header) {
    return icmp_header->icmp_type == ICMP_ECHOREPLY &&
           icmp_header->icmp_hun.ih_idseq.icd_id == getpid();
}

namespace icmp_prot {
void Receiver::receive_packets(
    int& sockfd, std::chrono::high_resolution_clock::time_point& recv_start,
    int& ttl) {
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
            size_t packet_len =
                recvfrom(sockfd, buffer, IP_MAXPACKET, 0,
                         (struct sockaddr*)&sender, &sender_len);

            if (packet_len > 0) {
                char ip_str[20];
                inet_ntop(AF_INET, &(sender.sin_addr), ip_str, sizeof(ip_str));

                struct ip* ip_header = (struct ip*)buffer;
                u_int8_t* icmp_packet = buffer + 4 * ip_header->ip_hl;
                struct icmp* icmp_header = (struct icmp*)icmp_packet;

                bool icmp_echo_reply = icmp_echo_reply_verify(icmp_header);
                if (icmp_time_exceeded_verify(icmp_header, ttl) ||
                    icmp_echo_reply) {
                    int rtt =
                        std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::high_resolution_clock::now() -
                            recv_start)
                            .count();
                    response_times.push_back(rtt);
                    responding_ips.push_back(ip_str);

                    if (icmp_echo_reply) {
                        std::cout << responding_ips[0] << " " << rtt << "ms"
                                  << std::endl;
                        exit(EXIT_SUCCESS);
                    }
                    received_count++;
                }
            } else {
                std::cerr << "Error receiving packet" << std::endl;
            }

        } else {
            break;
        }
    }
    if (received_count < 3) {
        std::cout << "*" << std::endl;
    } else {
        for (const auto& ip : responding_ips) {
            std::cout << ip << " ";
        }
        if (response_times.size() < 3) {
            std::cout << "???" << std::endl;
        } else {
            int rtt_avg = std::accumulate(response_times.begin(),
                                          response_times.end(), 0) /
                          response_times.size();
            std::cout << rtt_avg << "ms" << std::endl;
        }
    }
}
} // namespace icmp_prot
