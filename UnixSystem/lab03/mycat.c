#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFSIZE 4096
char buf[BUFFSIZE];

int main(int argc, char *argv[])
{
  int fd, n;

  if((fd = open(argv[1], O_RDONLY)) == -1) {
    perror("open");
    exit(1);
  }

  while((n = read(fd, buf, BUFFSIZE)) >0) {
    if(write(STDOUT_FILENO, buf, n) != n) {
      perror("write");
      exit(1);
    }
  }

  if(n<0) {
    perror("read");
    exit(1);
  }


  close(fd);
  exit(0);
}
