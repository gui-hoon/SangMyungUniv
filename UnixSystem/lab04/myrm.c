#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int myrm(const char *path) {
  if (unlink(path) == -1) {
    perror("unlink");
    exit(1);
  }

  return 0;
}

int main(int argc, char *argv[])
{
  int i;
  for (i=1; i<argc; i++)
    myrm(argv[i]);

  return 0;
}

