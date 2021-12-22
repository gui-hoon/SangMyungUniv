#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mydate(void) {
  time_t *t = (time_t *)malloc(sizeof(time_t));
  char *str;

  if (time(t) == -1) {
    perror("time");
    exit(1);
  }

  printf("%lu\n", *t);

  if ((str = ctime(t)) == NULL) {
    perror("ctime");
    exit(1);
  }

  printf("%s",str);
  free(t);
}

int main(void)
{
  mydate();

  return 0;
}

