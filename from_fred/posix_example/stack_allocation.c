#include <stdio.h>

int main(int argc, char **argv) {
  // Permission read/write et sur le stack (pile)
  char msg[] = "Hello world\n";
  msg[0] = 'A';
  puts(msg);
  return 0;
}
