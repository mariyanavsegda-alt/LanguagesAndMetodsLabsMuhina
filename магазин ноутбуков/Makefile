CC = gcc
CFLAGS = -Wall -std=c99
TARGET = laptop_store
SOURCES = main.c baza_noutov.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
