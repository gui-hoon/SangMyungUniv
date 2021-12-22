#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int pid;

void sigalarm_handler() {
  exit(0);
}

void sigusr_handler() {
  if (pid==0)
    printf("child...\n");
  else
    printf("parent...\n");
}

int main(void)
{

  if(signal(SIGUSR1, sigusr_handler) == SIG_ERR) {
    perror("signal");
    exit(1);
  }
    
  if(signal(SIGALRM, sigalarm_handler) == SIG_ERR) {
    perror("signal");
    exit(1);
  }

  pid = fork();

  if (pid < 0) {
    perror("fork");
    exit(1);
  }

  else if (pid == 0) {
    alarm((unsigned int)10);
    for(;;) {
      sleep(1);
      kill(getppid(), SIGUSR1);
      pause();
    }
  }

  else {
    alarm((unsigned int)10);
    for(;;) {
      pause();
      sleep(1);	
      kill(pid, SIGUSR1);
    }
  }

}

