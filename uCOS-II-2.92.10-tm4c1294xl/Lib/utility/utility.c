// ======================================================================
// File: utility.c
// ======================================================================

#include "utility.h"

// ======================================================================

/*
unsigned short OS_GetRandom(unsigned short n)
{
  static unsigned int rand = 0;

  rand = rand * 1103515245 + 12345;
  return (unsigned short)((rand / 65536) % n);
}
*/

#define SYST_CVR        0xe000e018

unsigned short OS_GetRandom(unsigned short n)
{
  static unsigned int rand = 0;

  rand = rand + *((unsigned int *) SYST_CVR);
  return (unsigned short)(rand % n);
}

// ======================================================================
