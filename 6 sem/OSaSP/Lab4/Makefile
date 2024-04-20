CC = gcc
CFLAGS = -Wall -Wextra

EXECUTABLE = main

SOURCES = main.c

OBJECTS = $(SOURCES:.c=.o)

all: $(EXECUTABLE) clean

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)