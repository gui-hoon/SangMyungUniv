#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void sigusr_handler() {
  exit(0);
}

int main(int argc, char *argv[])
{
  alarm((unsigned int)atoi(argv[1]));

  if (signal(SIGALRM, sigusr_handler)==SIG_ERR) {
    perror("signal");
    exit(1);
  }

 for(;;) {
    printf("running...\n");
    sleep(1);
  }
  return 0;
}

