
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  pid_t pid;

  int value = 5;
  
  if(fork() == 0){
    value += 15;
    execlp("ls","ls",NULL);
    printf("Value = %d \n", value);
  }
  else {
    wait(NULL);
    printf("Value = %d \n", value);
  }
  printf("test \n");
  return 0;
}
