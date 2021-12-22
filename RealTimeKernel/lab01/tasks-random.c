// ======================================================================
// File: tasks-random.c
// ======================================================================

#include "ucos_ii.h"
#include "tm4c1294xl.h"
#include "utility.h"

// ======================================================================

#define TASK_STK_SIZE	512
#define N_TASKS		10

// ======================================================================

OS_STK TaskStartStk[TASK_STK_SIZE];
OS_STK TaskStk[N_TASKS][TASK_STK_SIZE];

// ======================================================================

void TaskStart(void *pdata);
void Task0(void *pdata);
void Task1(void *pdata);
void Task2(void *pdata);
void Task3(void *pdata);
void Task4(void *pdata);
void Task5(void *pdata);
void Task6(void *pdata);
void Task7(void *pdata);
void Task8(void *pdata);
void Task9(void *pdata);

char TaskData[N_TASKS];

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
  unsigned char i;

  OSSoCInit();			// The first task should call this.
  OSStatInit();

  OSTaskCreate(Task0,(void*)0,&TaskStk[0][TASK_STK_SIZE-1],20);
  OSTaskCreate(Task1,(void*)0,&TaskStk[1][TASK_STK_SIZE-1],21);
  OSTaskCreate(Task2,(void*)0,&TaskStk[2][TASK_STK_SIZE-1],22);
  OSTaskCreate(Task3,(void*)0,&TaskStk[3][TASK_STK_SIZE-1],23);
  OSTaskCreate(Task4,(void*)0,&TaskStk[4][TASK_STK_SIZE-1],24);
  OSTaskCreate(Task5,(void*)0,&TaskStk[5][TASK_STK_SIZE-1],25);
  OSTaskCreate(Task6,(void*)0,&TaskStk[6][TASK_STK_SIZE-1],26);
  OSTaskCreate(Task7,(void*)0,&TaskStk[7][TASK_STK_SIZE-1],27);
  OSTaskCreate(Task8,(void*)0,&TaskStk[8][TASK_STK_SIZE-1],28);
  OSTaskCreate(Task9,(void*)0,&TaskStk[9][TASK_STK_SIZE-1],29);

refresh:
  UARTputclear();
  UARTprintf("Real-time kernel: random tasks");
  UARTputgoto(0, 20);
  UARTprintf("Type any char to refresh the screen.");
  for (;;) {
    if (UARTgetc_nb() != -1)
      goto refresh;
    UARTputgoto(0, 1);
    UARTprintf("Ticks=%d, Tasks=%d, CPU=%d%%   ", OSTimeGet(), OSTaskCtr,
	       OSCPUUsage);
    OSTimeDly(100);
  }
}

// ======================================================================

void Task0(void *pdata)
{
   for(;;){
        OSTimeDly(5); 	
 	
	int x,y;
	unsigned short color;  

 	x = OS_GetRandom(50);
 	y = OS_GetRandom(16)+3;
 	color = OS_GetRandom(8)+30; 	
 	UARTputgoto(x,y);
 	UARTputcolor(color);
 	UARTputc('0');
  }
}
  
void Task1(void *pdata)
{
   for(;;){
        OSTimeDly(5);
        
	int x,y;
	unsigned short color;

        x = OS_GetRandom(50);
        y = OS_GetRandom(16)+3;
        color = OS_GetRandom(8)+30;
        UARTputgoto(x,y);
        UARTputcolor(color);
        UARTputc('1');
  }
}

void Task2(void *pdata)
{
   for(;;){
        OSTimeDly(5);
        
	int x,y;
	unsigned short color;

        x = OS_GetRandom(50);
        y = OS_GetRandom(16)+3;
        color = OS_GetRandom(8)+30;
        UARTputgoto(x,y);
        UARTputcolor(color);
        UARTputc('2');
  }
}

void Task3(void *pdata)
{
   for(;;){
        OSTimeDly(5);
        
	int x,y;
	unsigned short color;

        x = OS_GetRandom(50);
        y = OS_GetRandom(16)+3;
        color = OS_GetRandom(8)+30;
        UARTputgoto(x,y);
        UARTputcolor(color);
        UARTputc('3');
  }
}

void Task4(void *pdata)
{
   for(;;){
        OSTimeDly(5);
        
	int x,y;
	unsigned short color;

        x = OS_GetRandom(50);
        y = OS_GetRandom(16)+3;
        color = OS_GetRandom(8)+30;
        UARTputgoto(x,y);
        UARTputcolor(color);
        UARTputc('4');
  }
}

void Task5(void *pdata)
{
   for(;;){
        OSTimeDly(5);
        
	int x,y;
	unsigned short color;

        x = OS_GetRandom(50);
        y = OS_GetRandom(16)+3;
        color = OS_GetRandom(8)+30;
        UARTputgoto(x,y);
        UARTputcolor(color);
        UARTputc('5');
  }
}

void Task6(void *pdata)
{
   for(;;){
        OSTimeDly(5);
        
	int x,y;
	unsigned short color;

        x = OS_GetRandom(50);
        y = OS_GetRandom(16)+3;
        color = OS_GetRandom(8)+30;
        UARTputgoto(x,y);
        UARTputcolor(color);
        UARTputc('6');
  }
}


void Task7(void *pdata)
{
   for(;;){
        OSTimeDly(5);
        
	int x,y;
	unsigned short color;

        x = OS_GetRandom(50);
        y = OS_GetRandom(16)+3;
        color = OS_GetRandom(8)+30;
        UARTputgoto(x,y);
        UARTputcolor(color);
        UARTputc('7');
  }
}


void Task8(void *pdata)
{
   for(;;){
        OSTimeDly(5);
        
	int x,y;
	unsigned short color;

        x = OS_GetRandom(50);
        y = OS_GetRandom(16)+3;
        color = OS_GetRandom(8)+30;
        UARTputgoto(x,y);
        UARTputcolor(color);
        UARTputc('8');
  }
}
  
  
void Task9(void *pdata)
{
   for(;;){
        OSTimeDly(5);
        
	int x,y;
	unsigned short color;

        x = OS_GetRandom(50);
        y = OS_GetRandom(16)+3;
        color = OS_GetRandom(8)+30;
        UARTputgoto(x,y);
        UARTputcolor(color);
        UARTputc('9');
  }
}

// ======================================================================
