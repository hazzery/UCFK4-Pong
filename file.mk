# File:   Makefile
# Author: H. D. Parkes
# Date:   10 Nov 2022
# Description:  Makefile for Pong


#Project specific definitions
MAINFILE=main.c
BINARY=pong.out
CODEDIRS=. ../drivers ../drivers/avr ../utils ../common
INCDIRS=. ../drivers ../drivers/avr ../utils ../common ../fonts

#Compiler specific definitions
CC=avr-gcc
OPT=-00
DEPFLAGS=-MMD
MMCU=atmega32u2
INCLUDEALL=$(foreach Dir,$(INCDIRS),-I$(Dir))
CFLAGS = -mmcu=$(MMCU) -Os -Wall -Wstrict-prototypes -Wextra -g $(DEPFLAGS) $(INCLUDEALL)

#File specific definitions
MAINDEPS=$(MAINFILE:.c=.d)
CLFILES=
OBJECTS=
ALLDEPS=

#Flashing specific definitions
SIZE = avr-size
OBJCOPY = avr-objcopy
HEX = $(patsubst %.out,%.hex,$(BINARY))

# Default target.
all: $(BINARY)



$(MAINDEPS): $(MAINFILE)
	$(CC) -MM $^ -MF $@ $(INCLUDEALL)


# Link: create ELF output file from object files.
$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@

# Compile: create object files from C source files.
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	$(CC) -c $(CFLAGS) $< -o $@

# Target: clean project.
.PHONY: clean
clean:
	rm $(OBJECTS) $(DEPFILES) $(BINARY) $(HEX)


# Target: Flash hex onto board.
.PHONY: program
program: $(BINARY)
	$(OBJCOPY) -O ihex $(BINARY) $(HEX)
	dfu-programmer $(MMCU) erase; dfu-programmer $(MMCU) flash $(HEX); dfu-programmer $(MMCU) start
