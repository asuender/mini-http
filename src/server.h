#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>

typedef struct sockaddr sockaddr_t;
typedef struct sockaddr_in sockaddr_in_t;

void init_server_addr(sockaddr_in_t *addr, uint16_t port);
int make_socket(uint16_t port, sockaddr_in_t *addr);
