// ===========:wq===========================================================
// File: clock.c
// ======================================================================

#include "ucos_ii.h"
#include "tm4c1294xl.h"
#include "utility.h"
#include "fonts.h"

// ======================================================================

#define TASK_STK_SIZE	512

// ======================================================================

void TaskStart(void *pdata);
void DisplayClock(void *pdata);

void timer_callback(void *ptmr, void *parg);

INT32U min, sec;
int key;

// ======================================================================

OS_STK TaskStartStk[TASK_STK_SIZE];
OS_STK DisplayClockStk[TASK_STK_SIZE];

OS_EVENT *Sem;
OS_TMR *Timer;

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
  INT8U err, serr, clock;
  min = 0;
  sec = 0;

  OSSoCInit();                  // The first task should call this.
  OSStatInit();

  Sem = OSSemCreate(1);
  Timer = OSTmrCreate(0, 10, OS_TMR_OPT_PERIODIC, timer_callback, (void *)0, &clock, &err);
  OSTaskCreate(DisplayClock, (void*)0, &DisplayClockStk[TASK_STK_SIZE-1], 20);
  OSTmrStart((OS_TMR *)Timer, &err);

  UARTputgoto(0,0);
  UARTprintf("uC/OS-II: clock");

  UARTputgoto(0,13);
  UARTprintf("Type \'M\'/\'m\' or \'S\'/\'s\' to adjust min and sec.");

  for(;;)
    {  
      key = 1;
      OSSemPend(Sem, 0, &serr);
      UARTputgoto(0,1);
      UARTprintf("Time=%d%d:%d%d, Tasks=%d, CPU=%d%%", min/10, min%10, sec/10, sec%10, OSTaskCtr, OSCPUUsage);
      OSSemPost(Sem);
      
      while(key!=-1){
        key = UARTgetc_nb();
        if(key == 'M'){
          if(min==59)
            min=0;
          else
            min++;
        }
      
        else if(key == 'm'){
          if(min==0) 
            min=59;
          else 
            min--;
        }
        else if(key == 'S'){
          if(sec==59){
            sec=0;
            min++;
          }
          else
            sec++;
        }

        else if(key == 's'){
          if((sec==0) && (min==0)){
            min=59;
            sec=59;
          }

          else if((sec==0) && (min!=0)){
            min--;
            sec=59;
          }
          else{
            sec--;
          }

        } 

        else if((key =='\r') || (key == '\n')){
            UARTputclear();
            UARTputgoto(0,0);
            UARTprintf("uC/OS-II: clock");
            UARTputgoto(0,13);
            UARTprintf("Type \'M\'/\'m\' or \'S\'/\'s\' to adjust min and sec.");
        } 
      }
      if(min==60) min = 0;
      OSTimeDly(100);
    }
}


// ======================================================================

void DisplayClock(void *pdata)
{
  INT32U m1,m2,s1,s2;
  INT32U i, j, asc = 79;
  INT8U serr;

  for(;;){

    m1 = min/10, m2 = min%10;
    s1 = sec/10, s2 = sec%10;

    if((key != -1) && (key !='M') && (key != 'm') && (key !='S') &&(key != 's'))
      asc = key;

    else
      OSTimeDly(0);

    OSSemPend(Sem, 0, &serr);

    UARTputgoto(0,3);
    for(i=3; i<12; i++){
      for(j=0; j<8; j++)
        {
          if(font_table[m1+16].font[i-3][j]==0)
            UARTprintf(" ");

          else if(font_table[m1+16].font[i-3][j]==1)
            UARTprintf("%c", asc);
        }
      UARTputgoto(0,i+1);
    }
	
    UARTputgoto(8,3);	
    for(i=3; i<12; i++){
      for(j=8; j<16; j++)
        {

          if(font_table[m2+16].font[i-3][j-8]==0)
            UARTprintf(" ");

          else if(font_table[m2+16].font[i-3][j-8]==1)
            UARTprintf("%c", asc);
        }
      UARTputgoto(8,i+1);
    }

    UARTputgoto(16,3);
    for(i=3; i<12; i++){
      for(j=16; j<24; j++)
        {

          if(font_table[26].font[i-3][j-16]==0)
            UARTprintf(" ");

          else if(font_table[26].font[i-3][j-16]==1)
            UARTprintf("%c", asc);
        }
      UARTputgoto(16,i+1);
    }

    UARTputgoto(24,3);
    for(i=3; i<12; i++){
      for(j=24; j<32; j++)
        {

          if(font_table[s1+16].font[i-3][j-24]==0)
            UARTprintf(" ");

          else if(font_table[s1+16].font[i-3][j-24]==1)
            UARTprintf("%c", asc);
        }
      UARTputgoto(24, i+1);
    }

    UARTputgoto(32,3);
    for(i=3; i<12; i++){
      for(j=32; j<40; j++)
        {

          if(font_table[s2+16].font[i-3][j-32]==0)
            UARTprintf(" ");

          else if(font_table[s2+16].font[i-3][j-32]==1)
            UARTprintf("%c", asc);
        }
      UARTputgoto(32, i+1);
    }
    OSSemPost(Sem);
    OSTimeDly(100);
  }
}

// ======================================================================

void timer_callback(void *ptmr, void *parg)
{
  sec++;

  if(min>=60){
    min = 0;
  }

  if(sec>=60){
    min++;
    sec=0;
  }
}

// ======================================================================
