#include <stdio.h>
#include <string.h>

// command: list
// user: **** anything
int main(void) {

  char command[30];
  char user[5];
  printf("Command: ");
  scanf(" %[^\n]", command);
  if(strncmp("list", command, 4) != 0) {
    fprintf(stderr, "Command must start with list\n");
    return 1;
  }
  printf("User: ");
  scanf(" %[^\n]", user);
  user[4] = '\0';
  printf("User %s execute command %s\n", user, command);
  return 0;
}
