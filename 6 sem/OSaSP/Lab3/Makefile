CC = gcc
CFLAGS = -Wall -Wextra

EXECUTABLE = main

SOURCES = main.c morse.c

OBJECTS = $(SOURCES:.c=.o)

HEADERS = morse.h

all: $(EXECUTABLE) test clean

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^


%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

test: $(EXECUTABLE)
	./$(EXECUTABLE) input.txt output.txt
	diff output.txt expected_output.txt