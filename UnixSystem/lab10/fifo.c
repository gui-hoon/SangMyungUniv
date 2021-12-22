#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
int main(int argc, char *argv[])
{
  int pid, fd0, fd1;
  if (argc != 3) {
    fprintf(stderr, "usage: fifo com1 com2\n");
    exit(1);
  }
  if (mkfifo("fifo-file", 0644) == -1) {
    perror("mkfifo");
    exit(1);
  }
  if ((pid = fork()) == -1) {
    perror("fork");
    exit(1);
  } else if (pid == 0) { // child
    fd1 = open("fifo-file", O_WRONLY);
    dup2(fd1, 1);
    close(fd1);
    system(argv[1]);
    exit(0);
  } else { // parent
    fd0 = open("fifo-file", O_RDONLY);
    dup2(fd0, 0);
    close(fd0);
    system(argv[2]);
    unlink("fifo-file");
    exit(0);
  }
}
