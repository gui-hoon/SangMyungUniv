#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

void mysystem(void) {
  struct utsname *buf = (struct utsname *)malloc(sizeof(struct utsname));

  if (uname(buf) == -1) {
    perror("uname");
    exit(1);
  }

  fprintf(stdout, "%s\n%s\n%s\n%s\n%s\n", buf->sysname, buf->nodename, buf->release, buf->version, buf->machine);

  free(buf);
}

int main(int argc, char *argv[])
{
  mysystem();

  return 0;
}
