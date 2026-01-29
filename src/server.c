#include "server.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int make_socket(uint16_t port, sockaddr_in_t *addr) {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (bind(sockfd, (sockaddr_t *)addr, sizeof(*addr)) < 0) {
    return -1;
  }

  return sockfd;
}

void init_server_addr(sockaddr_in_t *addr, uint16_t port) {
  /* Clear out the address before initializing */
  bzero((char *)addr, sizeof(*addr));

  addr->sin_family = AF_INET;
  addr->sin_port = htons(port);
  addr->sin_addr.s_addr = INADDR_ANY;
}
