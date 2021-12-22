#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{ 
  int sum = 0;
  
  for(int i = 1; i < argc; i++) {
    fprintf(stdout,"%d ",atoi(argv[i]));
    sum += atoi(argv[i]);
  }
  fprintf(stdout,"\nsum=%d\n",sum);
    
  exit(0);
}
