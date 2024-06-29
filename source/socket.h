#ifndef MIRA_SOCKET_H
#define MIRA_SOCKET_H

#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "common.h"

#define htonll(x) ((1 == htonl(1)) ? (x) : ((uint64_t) htonl((x) & 0xFFFFFFFF) << 32) | htonl((x) >> 32))
#define ntohll(x) ((1 == ntohl(1)) ? (x) : ((uint64_t) ntohl((x) & 0xFFFFFFFF) << 32) | ntohl((x) >> 32))

void Socket_SetBlocks(int fd, bool blocks);

#endif
