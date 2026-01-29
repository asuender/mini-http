TARGET = main
CC = gcc
CFLAGS = -Wall

.PHONY: default all clean

default: $(TARGET)

$(TARGET): $(wildcard *.c) $(wildcard src/*.c)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)
