/*
 * Filename: data_allocation.c
 * Author: Frédéric Hamel
 *
 * Montre les différente sorte d'allocation.
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  char *msg = "Un message."; // Mauvais, devrait avoir le qualificatif const.
  // const char *msg = "Un message."; // Bien!!!
  // char msg[] = "Un message"; // Bien, alloué sur la pile (stack)
  
  msg[0] = 'u'; // Valide que pour le 3e cas.
  return 0; 
}
