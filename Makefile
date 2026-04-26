CC				:= gcc
CFLAGS 			:= -std=c11 -Wall -pedantic
LFLAGS			:= -L./libnac -static -lnac
IFLAGS			:= -I./libnac

DEL				:= rm -f

all: nc-cli

clean:
	$(DEL) nc-cli

nc-cli: cli.c cli/display.c cli/input.c
	$(CC) $(CFLAGS) $^ $(IFLAGS) -I./cli $(LFLAGS) -o $@

.PHONY: clean
