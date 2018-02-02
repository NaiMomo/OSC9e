/**
 * Author: Frédéric Hamel
 * Filename: sys_getcwd_main.c
 *
 * Exemple d'appel d'un `wrapper`
 * de syscall fait en assembleur de C.
 */

#include <stdio.h>

extern size_t sys_getcwd(char *buf, size_t size);

int main(int argc, char **argv) {
  const size_t CWD_SIZE = 4096;
  char buf[CWD_SIZE];
  sys_getcwd(buf, CWD_SIZE);
  printf("pwd: %s\n", buf);
  return 0;
}
