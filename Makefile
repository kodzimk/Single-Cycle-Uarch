CC = gcc
CFLAGS=-Wall -Wextra -Wswitch-enum -Wconversion -std=c11 -pedantic

.PHONY: all
all: kodt kodc

kodt: kodt.c ./src/kodt.h
	$(CC) $(CFLAGS) -o kodt kodt.c $(LIBS)

kodc: kodc.c ./src/kodc.h
	$(CC) $(CFLAGS) -o kodc kodc.c $(LIBS)