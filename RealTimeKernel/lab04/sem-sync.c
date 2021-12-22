// ======================================================================
// File: sem-sync.c
// ======================================================================

#include "ucos_ii.h"
#include "tm4c1294xl.h"
#include "utility.h"

// ======================================================================

#define TASK_STK_SIZE	512

// ======================================================================

void TaskStart(void *pdata);
OS_STK TaskStartStk[TASK_STK_SIZE];

void Task1(void *pdata);
void Task2(void *pdata);

OS_STK Task1Stk[TASK_STK_SIZE];
OS_STK Task2Stk[TASK_STK_SIZE];

OS_EVENT * Sem1;
OS_EVENT * Sem2;

// ======================================================================

int main(void)
{
  OSInit();

  Sem1 = OSSemCreate(1);
  Sem2 = OSSemCreate(0);
    
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
  OSTaskCreate(Task2, (void *) 0, &Task2Stk[TASK_STK_SIZE - 1], 30);
  
  UARTputclear();    
  OSTaskDel(OS_PRIO_SELF);
}

// ======================================================================

void Task1(void *pdata)
{
  unsigned char err;

  for(;;){
    OSSemPend(Sem1, 0, &err);
    UARTputcolor(31);
    UARTprintf("[Task1]");
    OSSemPost(Sem2);
    OSTimeDly(OS_GetRandom(200));
  }
}

// ======================================================================

void Task2(void *pdata)
{
  unsigned char err;

  for(;;){
    OSSemPend(Sem2, 0, &err);
    UARTputcolor(34);
    UARTprintf("[Task2]");
    OSSemPost(Sem1);
    OSTimeDly(OS_GetRandom(200));
  }
}

// ======================================================================
