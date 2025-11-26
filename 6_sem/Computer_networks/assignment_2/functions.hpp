#pragma once
#include <arpa/inet.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <exception>
#include <fcntl.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <poll.h>
#include <stddef.h>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

struct pair_size_t {
  size_t start;
  size_t length;

  pair_size_t(size_t s, size_t l) : start(s), length(l) {}
};

u_int16_t conver_str_to_uint16(const char *str);

size_t conver_str_to_size_t(const char *str);

void set_server_address(struct sockaddr_in &server_address, u_int16_t &PORT,
                        const char *IP_ADDRESS);
// Send funtions
ssize_t sent_to_server(struct sockaddr_in &server, u_int8_t *buffer,
                       size_t &buffer_size, int &sockfd);
// To fix, later we will want to sent without pre computing vector array
std::vector<pair_size_t> divide_into_dgram(size_t FILE_SIZE,
                                           size_t max_dgram_size = 1000);

// receive functions
ssize_t receive_packet(int sockfd, u_int8_t *buffer, size_t buffer_size,
                       struct sockaddr_in &server_addr, int timeout_ms);

// Parssing function
bool parse_data_response(u_int8_t *buffer, ssize_t bytes_read, size_t &start,
                         size_t &length, u_int8_t **data_ptr);

// Moving window function
void moving_window(struct sockaddr_in &server_address, int &sockfd,
                   std::string FILE_NAME, size_t FILE_SIZE, int SWS,
                   size_t max_dgram_size = 1000);

struct window_element {
    pair_size_t dgram_info;
    bool received = false;
    u_int8_t *data_ptr = nullptr;
    u_int8_t buffer[1024];
    bool LAR = false;

    window_element(pair_size_t dgram_info, struct sockaddr_in &server_address,
                    int &sockfd) : dgram_info(dgram_info) {
        sent_elem(server_address, sockfd);
        received = receive_elem(server_address, sockfd);
    }

    void sent_elem(struct sockaddr_in &server_address, int &sockfd);

    bool receive_elem(struct sockaddr_in &server_address, int &sockfd);
};

void write_into_file(std::string FILE_NAME, u_int8_t **data_ptr, size_t length);

void moving_window(struct sockaddr_in &server_address, int &sockfd,
                    std::string FILE_NAME, size_t FILE_SIZE,
                    int SWS, size_t max_dgram_size);
