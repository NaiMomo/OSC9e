/*
 * Author: Frédéric Hamel
 * Filename: chdir-example.c
 *
 * Exemple d'appel à la fonction chdir()
 * qui `wrap` un appel système. Il y a
 * aussi un appel getcwd() qui donne
 * le répertoire courrant.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CWD_MAX 4096

int main(int argc, char **argv) {
  char buf[CWD_MAX];
  getcwd(buf, CWD_MAX);
  printf("Current Working Directory: %s\n", buf);
  chdir("..");

  getcwd(buf, CWD_MAX);
  printf("Current Working Directory: %s\n", buf);
  return 0;
}
