// Mikołaj Karapka
// 339286

#ifndef ICMP_PROT_H
#define ICMP_PROT_H

#include <arpa/inet.h>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <netinet/ip_icmp.h>
#include <poll.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

namespace icmp_prot {

class Receiver {
  public:
    struct sockaddr_in sender;
    socklen_t sender_len = sizeof(sender);
    u_int8_t buffer[IP_MAXPACKET];

    struct pollfd ps;

    void receive_packets(
    int& sockfd,std::chrono::high_resolution_clock::time_point& recv_start);
};

class Sender {
  public:
    uint16_t seq_counter = 0;
    struct icmp header;
    struct sockaddr_in recipient;

    void set_header();
    void set_recipinet(const char* IP_adress);

    size_t sent_to_recipinet(int& sockfd);
};
} // namespace icmp_prot
#endif
