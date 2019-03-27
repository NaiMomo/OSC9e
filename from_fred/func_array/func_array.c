#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum {
  GET,
  POST,
  HEAD,
  HACK,
  NB_TYPE_REQUESTS
};

void get_handler(char *req, int sock);
void hack_me(char *req, int sock);
void unsupported(char *req, int sock);

void (*handler[NB_TYPE_REQUESTS])(char *, int) = {
  [GET] = get_handler,
  [POST] = unsupported,
  [HEAD] = unsupported,
  [HACK] = hack_me
};

void get_handler(char *req, int sock) {
  printf("GET\n");
}
void hack_me(char *req, int sock) {
  printf("hack_me\n");
}
void unsupported(char *req, int sock) {
  printf("What did you mean by that?\n");
}
int main() {
  srand(time(NULL));
  int cmd = rand() % 5;
  if ((unsigned)cmd < NB_TYPE_REQUESTS) {
    handler[cmd](NULL, cmd);
  } else {
    unsupported(NULL, cmd);
  }
  return 0;
}

