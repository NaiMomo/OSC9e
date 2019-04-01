#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <netdb.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
  int client_socket;
  struct sockaddr_in addr;


  if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket()");
    goto quit;
  }

  // wrap client_socket 


  // connect to 127.0.0.1:8080
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  addr.sin_port = htons(8080);
  if (connect(client_socket, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    perror("connect()");
    goto close_socket;
  }

  int x[] = { 0, 1 , 7 };
  int r = send(client_socket, x, sizeof(x), 0);	
  printf("%d\n",r);

close_socket:
  close(client_socket);
quit:
  return 0;
}
