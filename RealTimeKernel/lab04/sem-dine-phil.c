// ======================================================================
// File: sem-dine-phil.c
// ======================================================================

#include "ucos_ii.h"
#include "tm4c1294xl.h"
#include "utility.h"

// ======================================================================

#define NO_OF_PHILOSOPHERS	5
#define TASK_STK_SIZE	512

// ======================================================================

void TaskStart(void *pdata);
OS_STK TaskStartStk[TASK_STK_SIZE];

void TaskPhilosopher(void *pdata);
void TaskPrint(void *pdata);

OS_STK TaskPhilosopher0Stk[TASK_STK_SIZE];
OS_STK TaskPhilosopher1Stk[TASK_STK_SIZE];
OS_STK TaskPhilosopher2Stk[TASK_STK_SIZE];
OS_STK TaskPhilosopher3Stk[TASK_STK_SIZE];
OS_STK TaskPhilosopher4Stk[TASK_STK_SIZE];
OS_STK TaskPrintStk[TASK_STK_SIZE];

OS_EVENT *Sem;
OS_EVENT *Fork[NO_OF_PHILOSOPHERS];

int Philo[NO_OF_PHILOSOPHERS];
// ======================================================================

int main(void)
{
  OSInit();

  OSTaskCreate(TaskStart, (void *) 0, &TaskStartStk[TASK_STK_SIZE - 1],
	       10);

  OSStart();

  return 0;
}

// ======================================================================

void TaskStart(void *pdata)
{
  OSSoCInit();			// The first task should call this.
  OSStatInit();
  UARTputclear();

for(int i=0; i<5; i++){
    Fork[i]=OSSemCreate(1);
    Philo[i]=i;
  }

  Sem=OSSemCreate(1);

  OSTaskCreate(TaskPhilosopher,(void *) &Philo[0], &TaskPhilosopher0Stk[TASK_STK_SIZE -1],20);
  OSTaskCreate(TaskPhilosopher,(void *) &Philo[1], &TaskPhilosopher1Stk[TASK_STK_SIZE -1],21);
  OSTaskCreate(TaskPhilosopher,(void *) &Philo[2], &TaskPhilosopher2Stk[TASK_STK_SIZE -1],22);
  OSTaskCreate(TaskPhilosopher,(void *) &Philo[3], &TaskPhilosopher3Stk[TASK_STK_SIZE -1],23);
  OSTaskCreate(TaskPhilosopher,(void *) &Philo[4], &TaskPhilosopher4Stk[TASK_STK_SIZE -1],24);
  OSTaskCreate(TaskPrint, (void *)0, &TaskPrintStk[TASK_STK_SIZE -1],19);

  OSTaskDel(OS_PRIO_SELF);
}

// ======================================================================

void TaskPrint(void *pdata)
{
  INT32S key;
  INT32U tick, task, cpu;
  INT8U err;

  for(;;)
    {
      tick = OSTimeGet();
      task = OSTaskCtr;
      cpu = OSCPUUsage;
      key = UARTgetc_nb();

      OSSemPend(Sem, 0, &err);

      UARTputgoto(0,0);
      UARTputcolor(30);
      UARTprintf("Real-time kernel: dining philosophers");

      UARTputgoto(0,1);
      UARTputcolor(30);
      UARTprintf("Ticks=%d, Tasks=%d, CPU=%d%%\n", tick,task,cpu);

      UARTputgoto(0,9);
      UARTputcolor(30);
      UARTprintf("Type any char to refresh the screen.");

      if(key != -1)
        UARTputclear();

      OSSemPost(Sem);
      OSTimeDly(100);
    }
}

// ======================================================================

void TaskPhilosopher(void *pdata)
{
  INT8U err;
  int Left_fork= (*((int*)pdata));
  int Right_fork= (*((int*)pdata)+1)%5;

  for(;;){
    OSSemPend(Sem,0,&err);
    UARTputgoto(0, Left_fork+3);
    UARTputcolor(34);
    UARTprintf("Philosopher %d is thinking...", Left_fork);
    OSSemPost(Sem);
    OSTimeDly(200+OS_GetRandom(50));

    OSSemPend(Fork[Left_fork],0,&err);
    if(Fork[Right_fork]==Fork[Left_fork]){
      OSSemPost(Fork[Left_fork]);
      OSTimeDly(OS_GetRandom(30));
      continue;
    }
    OSSemPend(Fork[Right_fork],0,&err);

    OSSemPend(Sem,0,&err);
    UARTputgoto(0,Left_fork+3);
    UARTputcolor(31);
    UARTwrite("[K",6);
    UARTprintf("Philosopher %d is eating...", Left_fork);

    OSSemPost(Sem);
    OSTimeDly(200+OS_GetRandom(50));
    OSSemPost(Fork[Right_fork]);
    OSSemPost(Fork[Left_fork]);
  }
}

// ======================================================================
