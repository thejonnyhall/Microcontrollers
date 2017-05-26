#
# 	CAB202
#	Generic Makefile for compiling with floating point printf
#
#	B.Talbot, September 2015
#	Queensland University of Technology
#

# run as  make uart1 or make uart2

# Modify these
SRC1=uart1
SRC2=uart2

CAB202_LIB_DIR=../cab202_teensy

# The rest should be all good as is
FLAGS=-mmcu=atmega32u4 -Os -DF_CPU=8000000UL -std=gnu99 -Wall
LIBS=-Wl,-u,vfprintf -lprintf_flt -lcab202_teensy -lm

# Default 'recipe'
uart1:
	avr-gcc $(SRC1).c $(FLAGS) -I$(CAB202_LIB_DIR) -L$(CAB202_LIB_DIR) $(LIBS) -o $(SRC1).o
	avr-objcopy -O ihex $(SRC1).o $(SRC1).hex
	
uart2:
	avr-gcc $(SRC2).c $(FLAGS) -I$(CAB202_LIB_DIR) -L$(CAB202_LIB_DIR) $(LIBS) -o $(SRC2).o
	avr-objcopy -O ihex $(SRC2).o $(SRC2).hex

# Cleaning  (be wary of this in directories with lots of executables...)
clean:
	rm *.o
	rm *.hex
