# ======================================================================
# File: Makefile
# ======================================================================

TIVAWARE=/home/rk/SW-TM4C-2.2.0.295
MYTIVAWARE=../tm4c1294xl/

# ======================================================================

CC=arm-none-eabi-gcc
AS=arm-none-eabi-as
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump

# ======================================================================

CFLAGS=-mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -MD -std=c99 -Wall -pedantic -DPART_TM4C1294NCPDT -c -Os -DTARGET_IS_TM4C129_RA2 -I$(MYTIVAWARE) -I$(TIVAWARE) -Dgcc
LDFLAGS=-T $(MYTIVAWARE)/link.ld --entry ResetISR --gc-sections -L $(MYTIVAWARE)

# ======================================================================

all:	startup.o tm4c1294xl.o

# ======================================================================

indent:
	indent -i2 -kr -nfca *.c
	@rm -f *~

# ======================================================================

clean:
	@rm -f *~ *.d

# ======================================================================
