// ======================================================================

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "pinout.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

// ======================================================================
// 사용하는 SoC를 초기화하여 사용할 수 있게 해 주는 매크로

#define OSSoCInit()						\
  {								\
    extern uint32_t g_ui32SysClock;				\
    OS_CPU_SysTickInit(g_ui32SysClock / OS_TICKS_PER_SEC);	\
  }

// ======================================================================

// 문자 c를 출력함
char UARTputc(char c);

// 한 문자를 읽어서 리턴함
unsigned char UARTgetc(void);

// 한 문자를 읽어서 리턴함. 만약 읽을 문자가 없으면 기다리지 않고 -1을 리턴함.
int UARTgetc_nb(void);

// 화면을 지우는 문자열을 출력함
void UARTputclear(void);

// 커서를 화면의 위치 (x, y)로 보내는 문자열을 출력함
void UARTputgoto(int x, int y);

// 앞으로 출력할 문자의 색깔을 color로 변경함(아래 color 매크로 사용)
void UARTputcolor(unsigned int color);

#define	ANSI_COLOR_BLACK	30	// black color
#define	ANSI_COLOR_RED		31	// red color
#define	ANSI_COLOR_GREEN	32	// green color
#define	ANSI_COLOR_YELLOW	33	// yellow color
#define	ANSI_COLOR_BLUE		34	// blue color
#define	ANSI_COLOR_MAGENTA	35	// magenta color
#define	ANSI_COLOR_CYAN		36	// cyan color
#define	ANSI_COLOR_WHITE	37	// white color

// 함수 sprintf()와 같은 기능을 수행하는 함수
int UARTsprintf(char *out, const char *format, ...);

// 함수 printf()와 같은 기능을 수행하는 함수
void UARTprintf(const char *format, ...);

// ======================================================================
