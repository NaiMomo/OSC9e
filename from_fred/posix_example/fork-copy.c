/**
 * Filename: fork-copy.c
 * Author: Frédéric Hamel
 *
 * Ce fichier montre le résultat du copy-on-write
 * du fork.
 */
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int a = 45;
  pid_t pid = fork();
  if(pid == 0) {
    // Cette ecriture force un copie de l'espace
    // d'adressage.
    a = 50;
  } else {
    // Le parent attend sont enfant avant de continuer.
    wait(NULL);
  }

  printf("%s voit %d\n",
      pid ? "L'enfant" : "Le parent", a);
  return 0;
}
