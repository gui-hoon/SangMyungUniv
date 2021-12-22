#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFSIZE 524288
char buf[BUFFSIZE];

int main(int argc, char *argv[])
{
  int r_fd, w_fd, n;

  if((r_fd = open(argv[1], O_RDONLY)) == -1) {
    perror("open");
    exit(1);
  }

  if((w_fd = open(argv[2], O_CREAT | O_WRONLY | O_EXCL, 0644)) == -1) {
    perror("open");
    exit(1);
  }

  while((n = read(r_fd, buf, BUFFSIZE)) >0) {
    if(write(w_fd, buf, n) != n) {
      perror("write");
      exit(1);
    }
  }

  if (n<0) {
    perror("read");
    exit(1);
  }

  close(r_fd);
  close(w_fd);
  exit(0);
}

