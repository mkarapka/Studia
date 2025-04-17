// Mikołaj Karapka
// 339286

#include "icmp_proto.hpp"
#include <assert.h>
#include <cstring>

u_int16_t compute_icmp_checksum(const void* buff, int length) {
    const u_int16_t* ptr =
        static_cast<const u_int16_t*>(buff);
    u_int32_t sum = 0;
    assert(length % 2 == 0);
    for (; length > 0; length -= 2)
        sum += *ptr++;
    sum = (sum >> 16U) + (sum & 0xffffU);
    return ~(sum + (sum >> 16U));
}

namespace icmp_prot {
void Sender::set_header(uint16_t ttl, uint16_t j) {
    header.icmp_type = ICMP_ECHO;
    header.icmp_code = 0;
    header.icmp_hun.ih_idseq.icd_id = getpid();
    header.icmp_hun.ih_idseq.icd_seq = 10 * ttl + j;
    header.icmp_cksum = 0;
    header.icmp_cksum = compute_icmp_checksum(
        (u_int16_t*)&header, sizeof(header)
    );
}

void Sender::set_recipinet(const char* IP_adress) {
    memset(&recipient, 0, sizeof(recipient));
    recipient.sin_family = AF_INET;
    inet_pton(AF_INET, IP_adress, &recipient.sin_addr);
}

size_t Sender::sent_to_recipinet(int& sockfd){
    ssize_t bytes_sent = sendto(
        sockfd,
        &header,
        sizeof(header),
        0,
        (struct sockaddr*)&recipient,
        sizeof(recipient)
    );
    return bytes_sent;
}
} // namespace icmp_prot
