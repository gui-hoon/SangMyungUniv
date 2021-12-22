#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(void)
{
  for (char **env = environ; *env; env++) {
    fprintf(stdout, "%s\n", *env);
  }

  exit(0);
}
