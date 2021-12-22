#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int exitno = atoi(argv[1]);

  fprintf(stdout,"exit=%d\n",exitno);
  exit(exitno);
}
