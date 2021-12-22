// ======================================================================

#include "tm4c1294xl.h"

// ======================================================================

uint32_t g_ui32SysClock;	// System clock rate in Hz.

void tm4c1294xl_init(void)
{
  // Run from the PLL at 120 MHz.
  // Note: SYSCTL_CFG_VCO_240 is a new setting provided in TivaWare 2.2.x and
  // later to better reflect the actual VCO speed due to SYSCTL#22.
  //
  g_ui32SysClock =
      MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
			      SYSCTL_USE_PLL | SYSCTL_CFG_VCO_240),
			     120000000);

  //
  // Configure the device pins.
  //
  PinoutSet(false, false);

  //
  // Enable the GPIO pins for the LED D1 (PN1).
  //
  MAP_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);

  //
  // Initialize the UART.
  //

  //
  // Enable the GPIO Peripheral used by the UART.
  //

  // Configure the UART and its pins.  This must be called before UARTprintf().
  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  //
  // Enable UART0
  //
  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

  //
  // Configure GPIO Pins for UART mode.
  //
  MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
  MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
  MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

  //
  // Initialize the UART for console I/O.
  //
  UARTStdioConfig(0, 115200, g_ui32SysClock);
}

// ======================================================================

char UARTputc(char c)
{
  UARTwrite(&c, 1);

  return c;
}

// ======================================================================

void UARTputclear(void)
{
  UARTwrite("[H[J", 6);
}

// ======================================================================

void UARTputgoto(int x, int y)
{
  int i;
  char xx[4], yy[4];

  x++;
  y++;

  i = 0;
  if (y < 10) {
    yy[i++] = y % 10 | '0';
  } else if (y < 100) {
    yy[i++] = y / 10 | '0';
    yy[i++] = y % 10 | '0';
  }
  yy[i++] = 0;

  i = 0;
  if (x < 10) {
    xx[i++] = x % 10 | '0';
  } else if (x < 100) {
    xx[i++] = x / 10 | '0';
    xx[i++] = x % 10 | '0';
  }
  xx[i++] = 0;

  UARTwrite("[", 2);
  UARTwrite(yy, 4);
  UARTwrite(";", 1);
  UARTwrite(xx, 4);
  UARTwrite("H", 1);
}

// ======================================================================

void UARTputcolor(unsigned int color)
{
  UARTwrite("[", 2);
  switch (color) {
  case ANSI_COLOR_BLACK:
    UARTwrite("30", 2);
    break;
  case ANSI_COLOR_RED:
    UARTwrite("31", 2);
    break;
  case ANSI_COLOR_GREEN:
    UARTwrite("32", 2);
    break;
  case ANSI_COLOR_YELLOW:
    UARTwrite("33", 2);
    break;
  case ANSI_COLOR_BLUE:
    UARTwrite("34", 2);
    break;
  case ANSI_COLOR_MAGENTA:
    UARTwrite("35", 2);
    break;
  case ANSI_COLOR_CYAN:
    UARTwrite("36", 2);
    break;
  case ANSI_COLOR_WHITE:
    UARTwrite("37", 2);
    break;
  default:
    UARTwrite("30", 2);
    break;
  }
  UARTwrite("m", 1);
}

// ======================================================================

#define PAD_RIGHT	1
#define PAD_ZERO	2
#define PRINT_BUF_LEN	12
#define MAX_UART_LINE	256

// ======================================================================

void printchar(char **str, int c)
{
  if (str) {
    **str = c;
    ++(*str);
  } else
    (void) UARTputc(c);
}

// ======================================================================

int prints(char **out, const char *string, int width, int pad)
{
  register int pc = 0, padchar = ' ';

  if (width > 0) {
    register int len = 0;
    register const char *ptr;
    for (ptr = string; *ptr; ++ptr)
      ++len;
    if (len >= width)
      width = 0;
    else
      width -= len;
    if (pad & PAD_ZERO)
      padchar = '0';
  }
  if (!(pad & PAD_RIGHT)) {
    for (; width > 0; --width) {
      printchar(out, padchar);
      ++pc;
    }
  }
  for (; *string; ++string) {
    printchar(out, *string);
    ++pc;
  }
  for (; width > 0; --width) {
    printchar(out, padchar);
    ++pc;
  }

  return pc;
}

// ======================================================================

int printi(char **out, int i, int b, int sg, int width, int pad,
	   int letbase)
{
  char print_buf[PRINT_BUF_LEN];
  register char *s;
  register int t, neg = 0, pc = 0;
  register unsigned int u = i;

  if (i == 0) {
    print_buf[0] = '0';
    print_buf[1] = '\0';
    return prints(out, print_buf, width, pad);
  }

  if (sg && b == 10 && i < 0) {
    neg = 1;
    u = -i;
  }

  s = print_buf + PRINT_BUF_LEN - 1;
  *s = '\0';

  while (u) {
    t = u % b;
    if (t >= 10)
      t += letbase - '0' - 10;
    *--s = t + '0';
    u /= b;
  }

  if (neg) {
    if (width && (pad & PAD_ZERO)) {
      printchar(out, '-');
      ++pc;
      --width;
    } else {
      *--s = '-';
    }
  }

  return pc + prints(out, s, width, pad);
}

// ======================================================================

int print(char **out, int *varg)
{
  register int width, pad;
  register int pc = 0;
  register char *format = (char *) (*varg++);
  char scr[2];

  for (; *format != 0; ++format) {
    if (*format == '%') {
      ++format;
      width = pad = 0;
      if (*format == '\0')
	break;
      if (*format == '%')
	goto out;
      if (*format == '-') {
	++format;
	pad = PAD_RIGHT;
      }
      while (*format == '0') {
	++format;
	pad |= PAD_ZERO;
      }
      for (; *format >= '0' && *format <= '9'; ++format) {
	width *= 10;
	width += *format - '0';
      }
      if (*format == 's') {
	register char *s = *((char **) varg++);
	pc += prints(out, s ? s : "(null)", width, pad);
	continue;
      }
      if (*format == 'd') {
	pc += printi(out, *varg++, 10, 1, width, pad, 'a');
	continue;
      }
      if (*format == 'x') {
	pc += printi(out, *varg++, 16, 0, width, pad, 'a');
	continue;
      }
      if (*format == 'X') {
	pc += printi(out, *varg++, 16, 0, width, pad, 'A');
	continue;
      }
      if (*format == 'u') {
	pc += printi(out, *varg++, 10, 0, width, pad, 'a');
	continue;
      }
      if (*format == 'c') {
	/* char are converted to int then pushed on the stack */
	scr[0] = *varg++;
	scr[1] = '\0';
	pc += prints(out, scr, width, pad);
	continue;
      }
    } else {
    out:
      printchar(out, *format);
      ++pc;
    }
  }
  if (out)
    **out = '\0';
  return pc;
}

// ======================================================================

int UARTsprintf(char *out, const char *format, ...)
{
  register int *varg = (int *) (&format);
  return print(&out, varg);
}

// ======================================================================
