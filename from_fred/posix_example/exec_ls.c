#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main(void) {
  int status;
  pid_t pid = fork();
  if(pid < 0) {
    perror("Unable to fork");
    return EXIT_FAILURE;
  } else if (pid) {
    waitpid(pid, &status, 0); // wait(&status);
    printf("Clone terminate with status %d\n", status);
  } else {
    execlp("ls", "ls", "-lh", NULL);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
