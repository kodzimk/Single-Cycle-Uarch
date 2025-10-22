CC = gcc
CFLAGS = -Wall -g
TARGET = computer

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o  $(TARGET) VonNeumanModel/alu.h main.c

clean:
	rm -f $(TARGET)