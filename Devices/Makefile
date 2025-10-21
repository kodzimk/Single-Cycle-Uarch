CC = gcc
CFLAGS = -Wall -g
TARGET = trans

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o  $(TARGET) n_type_transistors.h $(TARGET).c

clean:
	rm -f $(TARGET)