CC				:= gcc
CFLAGS 			:= -std=c11 -Wall -pedantic
LFLAGS			:= -L./libnac -static -lnac
IFLAGS			:= -I./libnac

DEL				:= rm -f

all: terminal

clean:
	$(DEL) terminal

terminal: terminal.c
	$(CC) $(CFLAGS) $^ $(IFLAGS) $(LFLAGS) -o $@

.PHONY: clean
