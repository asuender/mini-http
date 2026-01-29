#include "src/socket.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080
#define SERVER_RESPONSE "HTTP/1.1 501 Not Implemented\nConnection: close\n"

#define log(fmt, ...)                                                          \
  do {                                                                         \
    if (mode == MODE_VERBOSE) {                                                \
      printf("* " fmt "\n", ##__VA_ARGS__);                                    \
    }                                                                          \
  } while (0)
#define error(msg) perror(msg);
#define error_exit(msg)                                                        \
  perror(msg);                                                                 \
  exit(EXIT_FAILURE);

typedef enum { MODE_NORMAL, MODE_VERBOSE } server_mode;

int main(int argc, char *argv[]) {
  /* CLI parsing */
  server_mode mode;

  // I know that supporting verbose mode only doesn't necessarily require
  // a for loop, but let's keep this for potential flags in the future
  for (size_t optind = 1; optind < argc && argv[optind][0] == '-'; optind++) {
    switch (argv[optind][1]) {
    case 'v':
      mode = MODE_VERBOSE;
      break;
    default:
      mode = MODE_NORMAL;
    }
  }

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

  // Print each header line in verbose mode
  char *line = buffer;
  char *crlf;
  while ((crlf = strstr(line, "\r\n")) != NULL) {
    // empty line marks end of headers
    if (crlf == line)
      break;
    log("%.*s", (int)(crlf - line), line);
    line = crlf + 2;
  }

  n = write(acc_sockfd, SERVER_RESPONSE, strlen(SERVER_RESPONSE) + 1);
  if (n < 0) {
    error_exit("Error writing to socket");
  }

  close(sockfd);
  close(acc_sockfd);

  return EXIT_SUCCESS;
}
