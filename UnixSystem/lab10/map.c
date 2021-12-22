#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define DATA_SIZE 1024 * 10
#define BSS_SIZE 1024 * 10
#define HEAP_SIZE 1024 * 10
#define SHM_SIZE 1024 * 10
#define STACK_SIZE 1024 * 10

char data[DATA_SIZE] = { 0, 0, };
char bss[BSS_SIZE];

int main(int argc, char *argv[])
{
  char stack[STACK_SIZE];
  int shm_id;
  char *heap, *shm;

  // text area
  printf("text area: %p\n", main);

  // data area
  printf("data area: %p to %p\n", &data[0], &data[DATA_SIZE - 1]);

  // bss area
  printf("bss area: %p to %p\n", &bss[0], &bss[BSS_SIZE - 1]);

  // heap area
  if ((heap = malloc(HEAP_SIZE)) == NULL) {
    perror("malloc");
    exit(1);
  }
  printf("heap area: %p to %p\n", heap, heap + HEAP_SIZE - 1);

  // shared memory
  if ((shm_id = shmget(IPC_PRIVATE, SHM_SIZE, 0600)) == -1) {
    perror("shmget");
    exit(1);
  }

  if ((shm = shmat(shm_id, 0, 0)) ==(void *) -1) {
    perror("shmat");
    exit(1);
  }
  printf("shm area: %p to %p\n", shm, shm + SHM_SIZE - 1);

  if (shmctl(shm_id, IPC_RMID, 0) == -1) {perror("shmctl");
    exit(1);
  };

  // stack area
  printf("stack area: %p to %p\n", &stack[0], &stack[STACK_SIZE - 1]);

  // args area
  printf("args area: %p\n", argv[0]);
  exit(0);
}
