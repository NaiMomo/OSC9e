/*
 * Author: Frédéric Hamel
 * Filename: fork.c
 *
 * Exemple d'appel a l'a fonction fork()
 * qui permet de dupliquer le processus
 * courrant.
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
  pid_t pid1 = fork();
  pid_t pid2 = fork();
  pid_t pid3 = fork();

  if (pid1 > 0) {
    waitpid(pid1, NULL, 0);
  }
  if (pid2 > 0) {
    waitpid(pid2, NULL, 0);
  }
  if (pid3 > 0) {
    waitpid(pid3, NULL, 0);
  }
  printf("pid1: %d\n", pid1);
  printf("pid2: %d\n", pid2);
  printf("pid3: %d\n", pid3);

  return 0;
}

