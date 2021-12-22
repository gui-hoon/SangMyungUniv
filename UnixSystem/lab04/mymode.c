#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int mymode(const char *path) {
  struct stat status;
  mode_t mode;

  if (lstat(path, &status) == -1) {
    perror("lstat");
    exit(1);
  }

  mode = status.st_mode & 07777;
  fprintf(stdout, "%05o %s\n", mode, path);
  return 0;
}

int main(int argc, char *argv[]) 
{
  int i;

  for (i=1; i<argc; i++)
    mymode(argv[i]);

  return 0;
}

