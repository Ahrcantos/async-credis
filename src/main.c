#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>

#include "value.h"

char *redis_command_read(int socket_fd);

void main() {

  int status;
  int socket_fd;
  struct addrinfo hints;
  struct addrinfo *servinfo;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  status = getaddrinfo(NULL, "6379", &hints, &servinfo);

  if(status != 0) {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }

  socket_fd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

  if(socket_fd == -1) {
    perror("open socket");
    exit(1);
  }

  if(bind(socket_fd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
    perror("bind");
    exit(1);
  }


  if(listen(socket_fd, 20) == -1) {
    perror("listen");
    exit(1);
  }

  struct sockaddr_storage remote_addr;
  socklen_t remote_addr_size = sizeof remote_addr;
  int remote_socket_fd;


  remote_socket_fd = accept(socket_fd, (struct sockaddr *)&remote_addr, &remote_addr_size);

  if(remote_socket_fd == -1) {
    perror("accept");
    exit(1);
  }


  struct redis_value_t *value;
  struct redis_string_t *str;

  str = redis_string_new("This is a test");
  redis_string_print(str);
  value = redis_value_new(REDIS_STRING_KIND, str);



  /* char *msg = "This is a message"; */
  /* int len = strlen(msg); */

  /* send(remote_socket_fd, msg, len, 0); */
  redis_command_read(remote_socket_fd);

  /* char buffer[256]; */
  /* int remote_status; */
  /* memset(buffer, '\0', 256); */

  /* remote_status = recv(remote_socket_fd, buffer, 256, 0); */

  /* printf("Got %d: %s", remote_status, buffer); */

  /* memset(buffer, '\0', 256); */
  /* remote_status = recv(remote_socket_fd, buffer, 256, 0); */
  /* printf("Got %d: %s", remote_status, buffer); */


  freeaddrinfo(servinfo);
}

struct redis_command_t {
};

char *redis_command_read(int socket_fd) {
  char *buffer;
  int read_bytes;
  int total_bytes;

  total_bytes = 0;
  buffer = malloc(1024);
  memset(buffer, '\0', 1024);

  do {
    read_bytes = recv(socket_fd, buffer + total_bytes, 1024, 0);

    if(read_bytes == -1) {
      perror("recv");
      exit(1);
    }

    total_bytes += read_bytes;
  } while(read_bytes > 0);


  printf("Read byes: %d", read_bytes);
  printf("Buffer: %s", buffer);

  return buffer;
}

