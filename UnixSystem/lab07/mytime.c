#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>

int main(int argc, char *argv[])
{
  struct tms buf;
  float s_time;
  float e_time;
  int pid;
  float tck = sysconf(_SC_CLK_TCK);

  s_time = times(&buf);
  printf("parent: fork...\n");
  pid=fork();
  if(pid < 0){
    perror("fork");
    exit(1);
  } else if(pid==0){
    printf("child: exec...\n");
    execvp(argv[1], argv+1);
    exit(0);
  } else {
    printf("parent: wait...\n");
    wait(NULL);
    printf("parent: exit...\n");

    e_time = times(&buf);

    printf("real: %.3f sec\n",(e_time - s_time)/tck);
    printf("usr: %.3f sec\n", (float)(buf.tms_cutime)/tck);
    printf("sys: %.3f sec\n", (float)(buf.tms_cstime)/tck);

    exit(0);
  }
}
