# Makefile
#
# Created on: 2014-08-09
#     Author: cya
#

# define the project name, and the cpu type
PRJ = 210-ult01tester
PRJLIB = ../../../Components
CPU = arm926ej-s

# specify tools to build this project
PREFIX = arm-none-eabi-
CC   = $(PREFIX)gcc
AS   = $(PREFIX)gcc
LD   = $(PREFIX)gcc
OP   = $(PREFIX)objcopy
OD   = $(PREFIX)objdump
SZ   = $(PREFIX)size

LDSCRIPT = $(PRJLIB)/210/FA210Dram.ld

# list C source files here
SRC  = ult-01-tester.c \
       $(PRJLIB)/210/uart/uart.c \
       $(PRJLIB)/210/timer/timer.c \
       $(PRJLIB)/xprintf/xprintf.c 
       
# list ASM source files here
ASRC = 

OBJS = $(ASRC:.s=.o) $(SRC:.c=.o) 

# list libs dir here
LIBDIR = 

# list build tools options here
CCFLAGS = -mcpu=$(CPU) -I $(PRJLIB) -c     
ASFLAGS = -mcpu=$(CPU)  -c
LDFLAGS = -nostartfiles -T $(LDSCRIPT) -lm -Wl,-Map=$(PRJ).map
OPFLAGS = -O binary
ODFLAGS = -h -S
SZFLAGS = 

#
# makefile rules
#

all: $(PRJ).elf

$(PRJ).elf: $(OBJS)
	$(LD) $(OBJS) -o  $@         $(LDFLAGS)
	$(SZ) $(PRJ).elf             $(SZFLAGS)
	$(OP) $(PRJ).elf $(PRJ).bin  $(OPFLAGS)

%.o : %.c
	$(CC) $< -o $@  $(CCFLAGS)
	
%.o : %.s
	$(AS) $< -o $@  $(ASFLAGS)
	
clean:
	rm  $(PRJ).* $(OBJS) 
	

