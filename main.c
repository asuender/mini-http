#include "src/server.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void error(const char *msg) { perror(msg); }

void error_exit(const char *msg) {
  error(msg);
  exit(1);
}

#define PORT 8080
#define SERVER_RESPONSE "HTTP/1.1 501 Not Implemented\n"

int main(int argc, char *argv[]) {
  int sockfd, acc_sockfd, n;
  char buffer[1024];
  socklen_t client_len;
  sockaddr_in_t server_addr, client_addr;

  init_server_addr(&server_addr, PORT);
  sockfd = make_socket(PORT, &server_addr);
  if (sockfd < 0) {
    error_exit("Error on creating a socket");
  }

  listen(sockfd, 5);

  client_len = sizeof(client_addr);
  acc_sockfd = accept(sockfd, (sockaddr_t *)&client_addr, &client_len);

  if (acc_sockfd < 0) {
    error_exit("Error on accepting a client");
  }

  bzero(buffer, 1024);
  n = read(acc_sockfd, buffer, 1023);
  if (n < 0) {
    error_exit("Error reading from socket");
  }
  printf("Received message from client:\n%s", buffer);

  n = write(acc_sockfd, SERVER_RESPONSE, strlen(SERVER_RESPONSE) + 1);
  if (n < 0) {
    error_exit("Error writing to socket");
  }

  close(sockfd);
  close(acc_sockfd);

  return EXIT_SUCCESS;
}
