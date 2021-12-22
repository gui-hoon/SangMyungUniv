#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
  int pid;
  int status;
  pid_t waitpid;

  pid = fork();

  if(pid < 0 ) {
    perror("fork");
    exit(1);
  }else if(pid == 0 ) {
    printf("child=%d\n", getpid());
  }else {
    printf("parent=%d\n", getpid());
    waitpid = wait(&status);

    if(waitpid == -1) {
      perror("wait");
      exit(1);
    }

    sleep(60);
  }

  return 0;
}
