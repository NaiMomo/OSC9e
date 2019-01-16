/**
 * This program forks a separate process using the fork()/exec() system calls.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  pid_t pid;

  pid = fork();
  pid = fork();

  printf("bonjour \n"); // how many times with this get printed?
  
  
  return 0;
}
