#include <stdio.h>
#include <stdlib.h>

int exitno;

void printExitNo(void)
{
  fprintf(stdout,"exit=%d\n",exitno);
}

int main(int argc, char *argv[])
{
  atexit(printExitNo);
  exitno = atoi(argv[1]);
  exit(exitno);
}
