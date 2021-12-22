#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
  printf("pid=%d", getpid());
  printf(", ");
  printf("ppid=%d\n", getppid());

  return 0;
}
