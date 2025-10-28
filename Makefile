CC = gcc
CFLAGS = -Wall -g
TARGET = uArch

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o  $(TARGET) SingleCycleProcessorEmulation/uArch.h main.c

clean:
	rm -f $(TARGET)