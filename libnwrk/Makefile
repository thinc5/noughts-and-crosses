CC				:= gcc
CFLAGS 			:= -std=c99 -Wall -pedantic -O -fPIC

AR				:= ar

DEL				:= rm -f

ifeq ($(DEBUG), 1)
    CFLAGS += -g -DDEBUG
endif


all: libnwrk.so libnwrk.a

clean:
	$(DEL) *.so *.o *.a

libnwrk.so: nwrk.c
	$(CC) $(CFLAGS) -shared $^ -o $@

libnwrk.o: nwrk.c
	$(CC) $(CFLAGS) -c $^ -o $@

libnwrk.a: nwrk.o
	$(AR) rcs $@ $^

.PHONY: clean
