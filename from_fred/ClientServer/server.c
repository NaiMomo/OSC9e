#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <errno.h>
#include <netdb.h>

#include <sys/poll.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

static int wait_connection(int server_socket, unsigned timeout) {
  struct sockaddr_in addr;
  socklen_t socklen = 0;
  unsigned end = time(NULL) + timeout;

  int  client_socket = -1;
  while(client_socket < 0) {
    // accept a client connection if available.
    client_socket = accept(server_socket, (struct sockaddr*)&addr, &socklen);
    if (time(NULL) > end) {
      break;
    }
    // Try again in 1s.
    sleep(1);
  }
  return client_socket;
}

int main(int argc, char **argv) {
  int server_socket, client_socket,
      accepting_connection = 1,
      timeout = 30; // 30 seconds
  struct sockaddr_in addr;
  addr.sin_family = AF_LOCAL;
  if((server_socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)) < 0) {
    perror("socket()");
    goto quit;
  }

  if( setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0 ) {
    perror("setsockopt()");
    goto close_socket;
  }

  // Set address to 127.0.0.1 port 8080
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  // Bind address to server socket.
  if (bind(server_socket, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    perror("bind()");
    goto close_socket;
  }

  // Set socket mode to listen.
  if (listen(server_socket, 5) < 0) {
    perror("listen()");
    goto close_socket;
  }

  // Loop that accept connection.
  while(accepting_connection) {
    client_socket = wait_connection(server_socket, timeout);
    if (client_socket > 0) {
      // Call function using the connection with the client.    
      int cmd;  
      recv(client_socket,&cmd,sizeof(cmd), 0);
      int size;
      read(client_socket,&size,sizeof(size));
      // dynamic stack allocation
      // int x[size];
      // read(client_socket,x,sizeof(x));

      // heap allocation
      int * x = malloc(size * sizeof(int)); 
      read(client_socket,x,size*sizeof(int));
      // cmd == BEGIN dans votre tp.
      // Ne pas mettre de "magic number" s.v.p
      if (cmd == 0)
        printf("Cmd: Begin\n");	  
      for(int i=0; i < size;i++)
        printf("Read: %d\n", x[i]);	
      free(x);
      accepting_connection = 0;
    }
  }
close_socket: 
  close(server_socket);
quit:
  return 0;
}

