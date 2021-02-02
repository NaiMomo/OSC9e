/**
 * This program forks a separate process using the fork()/exec() system calls.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  pid_t pid;

  /* fork a child process */
  pid = fork();

  
  if (pid < 0) { /* error occurred */
    fprintf(stderr, "Fork Failed\n");
    return 1;
  }
  else if (pid == 0) { /* child process */
    printf("I am the child %d\n",pid);
    execl("/bin/ls","ls",NULL);
  }
  else { /* parent process */

    printf("I am the parent %d\n",pid);

    pid_t pid2;
    pid2 = fork();

    if(pid2 < 0){ return 1; }
    else if (pid2 == 0){
      exit(1); /* second child exits with error */
    }
    else{
      
      printf("I am the parent %d\n",pid2);
      pid_t pid_return_val;
      int status;
      pid_return_val = waitpid(pid, &status, 0);

      printf("Child %d returns with status %d  \n",pid_return_val,WEXITSTATUS(status)); // what will the status be?

      pid_return_val = waitpid(pid2, &status, 0);

      printf("Child %d returns  with status %d \n",pid_return_val,WEXITSTATUS(status)); // what will the status be?

    }
  }

  printf("done\n"); //how many times is this executed?
  return 0;
}
