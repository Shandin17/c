/**
* @description функции для преобразования порядка байтов из сетевого (bid-endian )
 * в порядок данной машины
 * n - network
 * h - host
 * s - short (16 бит)
 * l - long (32 бита)
 * ntohl - network to host long
*/
unsigned int htonl(unsigned int hostlong);
unsigned short int htons(unsigned short int hostshort);
unsigned int ntohl(unsigned short int netlong);
unsigned short int ntohs(unsigned short int netshort);

// example

struct sockaddr_in addr;
addr.sin_port = htons(7654);