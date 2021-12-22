#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int mysize(const char *path) {
  struct stat status;
  off_t size;

  if (lstat(path, &status) == -1) {
    perror("lstat");
    exit(1);
  }

  size = status.st_size;
  fprintf(stdout, "%10ld %s\n", size, path);

  return 0;
}

int main(int argc, char *argv[])
{
  int i;

  for(i=1; i<argc; i++)
    mysize(argv[i]);

  return 0;
}

