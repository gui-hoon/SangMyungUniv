// ======================================================================
// File: sem-prod-cons.c
// ======================================================================

#include "ucos_ii.h"
#include "tm4c1294xl.h"
#include "utility.h"
// ======================================================================

#define TASK_STK_SIZE	512
#define	BUFFER_SIZE	9

// ======================================================================

void TaskStart(void *pdata);
OS_STK TaskStartStk[TASK_STK_SIZE];

void TaskProducer1(void *pdata);
void TaskProducer2(void *pdata);
void TaskConsumer1(void *pdata);
void TaskConsumer2(void *pdata);
void TaskPrinter(void *pdata);

OS_STK TaskProducer1Stk[TASK_STK_SIZE];
OS_STK TaskProducer2Stk[TASK_STK_SIZE];
OS_STK TaskConsumer1Stk[TASK_STK_SIZE];
OS_STK TaskConsumer2Stk[TASK_STK_SIZE];
OS_STK TaskPrinterStk[TASK_STK_SIZE];

OS_EVENT *Sem_full;
OS_EVENT *Sem_empty;
OS_EVENT *Sem;

// ======================================================================

struct {
  unsigned int Front, Rear;
  unsigned int Data[BUFFER_SIZE];
} Buffer = {0, 0,};

// ======================================================================

unsigned int producer_delay = 200;
unsigned int consumer_delay = 200;
unsigned int printer_delay = 20;

// ======================================================================

int AddToBuffer(int item);
int RemoveFromBuffer(void);
void PrintBuffer(void);

// ======================================================================

int main(void)
{
  OSInit();

  Sem_full = OSSemCreate(0);
  Sem_empty = OSSemCreate(BUFFER_SIZE-1);
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

  OSTaskCreate(TaskProducer1, (void *) 0, &TaskProducer1Stk[TASK_STK_SIZE-1], 21);
  OSTaskCreate(TaskProducer2, (void *) 0, &TaskProducer2Stk[TASK_STK_SIZE-1], 22);
  OSTaskCreate(TaskConsumer1, (void *) 0, &TaskConsumer1Stk[TASK_STK_SIZE-1], 23);
  OSTaskCreate(TaskConsumer2, (void *) 0, &TaskConsumer2Stk[TASK_STK_SIZE-1], 24);
  OSTaskCreate(TaskPrinter, (void *) 0, &TaskPrinterStk[TASK_STK_SIZE-1], 20);

  UARTputclear();
  UARTputcolor(30);
  UARTputgoto(0,0);
  UARTprintf("Real-time kernel: producer-consumer");

  UARTputcolor(30);
  UARTputgoto(0,9);
  UARTprintf("Type '+'/'-' to change the dly of consumers.");

  OSTaskDel(OS_PRIO_SELF);
}

// ======================================================================

void TaskProducer1(void *pdata)
{
  INT32U item;
  INT8U err1, err2;

  for(;;){

    item = OS_GetRandom(10000);

    OSSemPend(Sem_empty, 0, &err1);
    OSSemPend(Sem, 0, &err2);
    Buffer.Rear=AddToBuffer(item);

    UARTputgoto(0,3);
    UARTprintf("producer1 dly=%d: %d",producer_delay,item);

    OSSemPost(Sem_full);
    OSSemPost(Sem);

    OSTimeDly(producer_delay);
  }
}

void TaskProducer2(void *pdata)
{
  INT32U item;
  INT8U err1, err2;

  for(;;){

    item = OS_GetRandom(10000);

    OSSemPend(Sem_empty, 0, &err1);
    OSSemPend(Sem, 0, &err2);
    Buffer.Rear=AddToBuffer(item);

    UARTputgoto(0,4);
    UARTprintf("producer2 dly=%d: %d",producer_delay,item);

    OSSemPost(Sem_full);
    OSSemPost(Sem);

    OSTimeDly(producer_delay);
  }
}

// ======================================================================

void TaskConsumer1(void *pdata)
{
  INT32U item;
  INT8U err1, err2;

  for(;;){

    OSSemPend(Sem_full, 0, &err2);
    OSSemPend(Sem, 0, &err1);
    item=RemoveFromBuffer();

    UARTputgoto(0,6);
    UARTprintf("consumer1 dly=%d: %d",consumer_delay,item);

    OSSemPost(Sem_empty);
    OSSemPost(Sem);

    OSTimeDly(consumer_delay);
  }
}

void TaskConsumer2(void *pdata)
{
  INT32U item;
  INT8U err1, err2;

  for(;;){

    OSSemPend(Sem_full,0,&err2);
    OSSemPend(Sem,0,&err1);
    item=RemoveFromBuffer();

    UARTputgoto(0,7);
    UARTprintf("consumer2 dly=%d: %d",consumer_delay,item);

    OSSemPost(Sem_empty);
    OSSemPost(Sem);

    OSTimeDly(consumer_delay);
  }
}

// ======================================================================

void TaskPrinter(void *pdata)
{
  INT32S key;
  INT32U tick, task, cpu;
  INT8U err;

  for(;;){

    key = 1;
    tick = OSTimeGet();
    task = OSTaskCtr;
    cpu = OSCPUUsage;

    OSSemPend(Sem,0,&err);
    UARTputgoto(0,1);
    UARTprintf("Ticks=%d, Tasks=%d, CPU=%d%%\n", tick, task, cpu);

    UARTputgoto(0,5);
    UARTwrite("[K",6);
    PrintBuffer();

    while(key != -1) {
      key = UARTgetc_nb();
      if(key == '+') {
        if(consumer_delay < 250)
          consumer_delay+=10;
      }
      else if(key == '-') {
        if(consumer_delay > 150)
          consumer_delay-=10;
      }
    }

    OSSemPost(Sem);
    OSTimeDly(printer_delay);
  }
}

// ======================================================================

int AddToBuffer(int item)
{
  Buffer.Rear = (Buffer.Rear + 1) % BUFFER_SIZE;
  Buffer.Data[Buffer.Rear] = item;

  return Buffer.Rear;
}

// ======================================================================

int RemoveFromBuffer(void)
{
  unsigned int item;

  Buffer.Front = (Buffer.Front + 1) % BUFFER_SIZE;
  item = Buffer.Data[Buffer.Front];

  return item;
}

// ======================================================================      

void PrintBuffer(void)
{
  int i, j, size;

  size = Buffer.Rear >= Buffer.Front ? (Buffer.Rear - Buffer.Front) :
      (Buffer.Rear + BUFFER_SIZE - Buffer.Front);

  UARTprintf("Buffers[] len=%03d: ", size);
  j = Buffer.Front + 1;
  for (i = 0; i < size; i++) {
    UARTprintf("%d ", Buffer.Data[j % BUFFER_SIZE]);
    j = j + 1;
  }
}

// ======================================================================
