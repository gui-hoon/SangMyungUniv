#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MSGSIZE 1024

struct {
  long mtype;
  char mtext[MSGSIZE];
} msg_snd, msg_rcv;

int main(int argc, char *argv[])
{
  int msg_id;

  msg_id = msgget(IPC_PRIVATE, 0644 | IPC_CREAT);

  msg_snd.mtype = 1;
  strcpy(msg_snd.mtext, "This is a message 1.");
  msgsnd(msg_id, (void *) &msg_snd, MSGSIZE, 0);
  printf("msgsnd: %s\n", msg_snd.mtext);

  strcpy(msg_snd.mtext, "This is a message 2.");
  msgsnd(msg_id, (void *) &msg_snd, MSGSIZE, 0);
  printf("msgsnd: %s\n", msg_snd.mtext);
  strcpy(msg_snd.mtext, "This is a message 3.");
  msgsnd(msg_id, (void *) &msg_snd, MSGSIZE, 0);
  printf("msgsnd: %s\n", msg_snd.mtext);
  
  msgrcv(msg_id, (void *) &msg_rcv, MSGSIZE, 0, 0);
  printf("msgrcv: %s\n", msg_rcv.mtext);

  msgrcv(msg_id, (void *) &msg_rcv, MSGSIZE, 0, 0); 
  printf("msgrcv: %s\n", msg_rcv.mtext);
  
  msgrcv(msg_id, (void *) &msg_rcv, MSGSIZE, 0, 0);
  printf("msgrcv: %s\n", msg_rcv.mtext);

  msgctl(msg_id, IPC_RMID, 0);
  
  exit(0);
}
