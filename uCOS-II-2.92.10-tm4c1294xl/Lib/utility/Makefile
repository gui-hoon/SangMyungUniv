# ======================================================================
# File: Makefile
# ======================================================================

DIR = utility
PROG = utility
UTILITY_SRCS = $(PROG).c $(PROG).h
UTILITY_OBJS = $(PROG).o

# ======================================================================

CROSS_COMPILE = arm-none-eabi-

AS = $(CROSS_COMPILE)as
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
AR = $(CROSS_COMPILE)ar

# ======================================================================

CFLAGS=-mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -MD -std=c99 -Wall -pedantic -DPART_TM4C1294NCPDT -c -Os -DTARGET_IS_TM4C129_RA2 -I. -I$(UCOS_SOURCE_DIR) -I$(UCOS_PORT_DIR) -I$(LIB_TM4C1294_DIR) -I$(LIB_UTILITY_DIR) -I$(TIVAWARE_DIR) -Dgcc
#CFLAGS = -g -O3 -Wall -mcpu=cortex-m4 -mthumb -fno-builtin

# ======================================================================

lib$(PROG).a:	$(UTILITY_OBJS)
	$(AR) crv lib$(PROG).a $(UTILITY_OBJS)

# ======================================================================

indent:
	@indent -i2 -kr -nfca $(UTILITY_SRCS)
	@rm -f *~

# ======================================================================

clean:
	@rm -f *~ *.o *.d

clean-all:	clean
	@rm -f *.a

# ======================================================================
