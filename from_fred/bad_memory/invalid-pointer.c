#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *test1() {
  char input[100] = "Un message\n              ";
  char *ret = input;
  return ret; // strdup pour que avoir une copie de input sur le tas.
}

char *test2() {
  char input[100] = "Cocolapin, il est vilain\n";
  char *ret = input;
  return ret; // strdup pour que avoir une copie de input sur le tas.
}

int main(void) {
  char *result = test1();
  test2(); // free(test2()); pour libérer l'allocation de strdup.
  printf(result);
  free(result); // free(result); pour libérer l'allocation de strdup.
  return 0;
}
