#include <stdio.h>
#define __USE_GNU // enable execvpe
#include <unistd.h>

int main(int argc, char **argv) {
  char* const command[] = { "env", NULL };
  char* const env[] = {"HOME=/tmp", "FOO=bar", NULL};
  return execvpe(command[0], command, env);
}
