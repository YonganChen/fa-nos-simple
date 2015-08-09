# Makefile
#
# Created on: 2014-10-23
#     Author: cya
#

# define the project name, and the cpu type
PRJ = 6410-FMSi4703Test
CPU = arm926ej-s

# specify tools to build this project
PREFIX = arm-none-eabi-
CC   = $(PREFIX)gcc
AS   = $(PREFIX)gcc
LD   = $(PREFIX)gcc
OP   = $(PREFIX)objcopy
OD   = $(PREFIX)objdump
SZ   = $(PREFIX)size

LDSCRIPT = ../../Components/FA6410Dram.ld

# list C source files here
SRC  = main.c \
       ../../Components/uart/uart.c \
       ../../Components/xprintf/xprintf.c \
       ../../Components/delay/delay.c  \
       ../../Components/Si470x/si470x_io2w.c \
       ../../Components/Si470x/si470x_cmd.c \
       ../../Components/Si470x/si470x_wait.c 
       
# list ASM source files here
ASRC = 

OBJS = $(ASRC:.s=.o) $(SRC:.c=.o) 

# list libs dir here
LIBDIR = 

# list build tools options here
CCFLAGS = -mcpu=$(CPU)  -c     
ASFLAGS = -mcpu=$(CPU)  -c
LDFLAGS = -nostartfiles -T $(LDSCRIPT) -Wl,-Map=$(PRJ).map
OPFLAGS = -O binary
ODFLAGS = -h -S
SZFLAGS = 

#
# makefile rules
#

all: $(PRJ).elf

$(PRJ).elf: $(OBJS)
	$(LD) $(LDFLAGS)  $(OBJS) -o $@
	$(SZ) $(SZFLAGS)  $(PRJ).elf
	$(OP) $(OPFLAGS)  $(PRJ).elf $(PRJ).bin

%.o : %.c
	$(CC)  $(CCFLAGS) $< -o $@
	
%.o : %.s
	$(AS)  $(ASFLAGS) $< -o $@
	
clean:
	rm  $(PRJ).* $(OBJS) 
	

