CC				:= gcc
CFLAGS 			:= -std=c11 -Wall -pedantic -O -fPIC

AR				:= ar

DEL				:= rm -f

all: libnac.so libnac.a

clean:
	$(DEL) *.so *.o *.a

libnac.so: nac.c
	$(CC) $(CFLAGS) -shared $^ -o $@

libnac.o: nac.c
	$(CC) $(CFLAGS) -c $^ -o $@

libnac.a: nac.o
	$(AR) rcs $@ $^

.PHONY: clean
