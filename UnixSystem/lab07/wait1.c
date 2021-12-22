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
    printf("child=%d\n", getpid());
  }else {
    printf("parent=%d\n", getpid());
    sleep(60);
  }

  return 0;
}
