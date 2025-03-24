#ifndef ICMP_PROT_H
#define ICMP_PROT_H

#include <arpa/inet.h>
#include <cstdlib>
#include <netinet/ip_icmp.h>
#include <poll.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h> // Dla getpid()
#include <vector>
#include <iostream>
#include <stdexcept>


namespace icmp_prot {

class Receiver {
  public:


    struct sockaddr_in sender;
    socklen_t sender_len = sizeof(sender);
    u_int8_t buffer[IP_MAXPACKET];

    struct pollfd ps;
    std::vector<std::string> router_ips;

    void receive_packets(int& sockfd);
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
