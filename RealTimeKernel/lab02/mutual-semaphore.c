// ======================================================================
// File: mutual-semaphore.c
// ======================================================================

#include "ucos_ii.h"
#include "tm4c1294xl.h"
#include "utility.h"

// ======================================================================

#define TASK_STK_SIZE	512

// ======================================================================

void TaskStart(void *pdata);
void Task1(void *pdata);
void Task2(void *pdata);

OS_STK TaskStartStk[TASK_STK_SIZE];
OS_STK Task1Stk[TASK_STK_SIZE];
OS_STK Task2Stk[TASK_STK_SIZE];

OS_EVENT *Sem;

// ======================================================================

int main(void)
{
  OSInit();

  Sem = OSSemCreate(1);

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

  OSTaskCreate(Task1, (void *) 0, &Task1Stk[TASK_STK_SIZE - 1], 20);
  OSTaskCreate(Task2, (void *) 0, &Task2Stk[TASK_STK_SIZE - 1], 21);

  UARTputclear();

  OSTaskDel(OS_PRIO_SELF);
}

// ======================================================================

void Task1(void *pdata)
{
  INT8U err;

  for (;;) {
    OSSemPend(Sem, 0, &err);
    UARTprintf("11111111111111111111111111111111111111111111111111\n");
    OSSemPost(Sem);
    OSTimeDly(OS_GetRandom(5));   
  }
}

// ======================================================================

void Task2(void *pdata)
{
  INT8U err;

  for (;;) {
    OSSemPend(Sem, 0, &err);
    UARTprintf("22222222222222222222222222222222222222222222222222\n");
    OSSemPost(Sem);
    OSTimeDly(OS_GetRandom(5));
  }
}

// ======================================================================
