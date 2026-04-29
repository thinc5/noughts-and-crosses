# Tools
CC				:= gcc
FORMATTER		:= uncrustify

# Configuration files
FORMAT_CONFIG	:= style.cfg

# Compiler flags
CFLAGS 			:= -std=c99 -std=c11 -Wall -pedantic
LFLAGS			:= -L./libnac -L./libnwrk -static -lnac -lnwrk
IFLAGS			:= -I./libnac -I./libnwrk -I./core

FORMAT_TARGETS	:= $(shell find . -type f \( -name "*.c" -o -name "*.h" \))

DEL				:= rm -f

# If DEBUG=1 complie with debug symbols and behaviour.
ifeq ($(DEBUG), 1)
    CFLAGS += -g -DDEBUG
endif

all: format nc-cli

nc-cli: cli.c cli/display.c cli/input.c
	$(CC) $(CFLAGS) $^ $(IFLAGS) -I./cli $(LFLAGS) -o $@

format_clean:
	@$(DEL) **.unc*
	@$(DEL) **/**.unc*


$(FORMAT_TARGETS):
	@$(FORMATTER) -c $(FORMAT_CONFIG) -q -f $@ -o $@

format: $(FORMAT_TARGETS) format_clean

clean:
	$(DEL) nc-cli

.PHONY: clean format
