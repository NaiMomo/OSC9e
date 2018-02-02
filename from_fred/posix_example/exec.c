/*
 * Author: Frédéric Hamel
 * Filename: exec.c
 *
 * Exemple d'appel a execve qui permet de
 * passer un environnement à un l'image d'un
 * processus.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// List des variable d'environnement.
extern char **environ;

int main(int argc, char **argv) {
  char *env[] = {
    "HOME=/home/frederic",
    "TERM=rxvt-unicode", NULL };
  char *program[3] = { argv[0], "-f", NULL };
  if(argc == 1) {
    return execve(program[0], program, env);
  } else {
    for(char **s = environ; *s; ++s) {
      printf("%s\n", *s);
    }
  }
}
