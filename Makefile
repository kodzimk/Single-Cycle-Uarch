CC = gcc
CFLAGS=-Wall -Wextra -Wswitch-enum -Wconversion -std=c11 -pedantic 

.PHONY: all
all: kodt

kodt: kodt.c ./src/kodt.h
	$(CC) $(CFLAGS) -o kodt kodt.c $(LIBS)

clean:
	rm -f $(TARGET)