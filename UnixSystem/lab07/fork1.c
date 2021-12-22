#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int pid;

  pid = fork();

  if(pid < 0 ) {
    perror("fork");
    exit(1);
  }else if(pid == 0 ) {
    printf("child pid: %d\n", getpid());
  }else {
    printf("parent pid: %d\n", getpid());
    printf("parent return pid: %d\n", pid);
  }
  
  return 0;
}
