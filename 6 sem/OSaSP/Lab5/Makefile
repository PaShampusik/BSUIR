CC = gcc
CFLAGS = -Wall -Wextra
LIBS += -lm
EXECUTABLE = main

SOURCES = main.c sort.c

HEADERS = sort.h

OBJECTS = $(SOURCES:.c=.o)

all: $(EXECUTABLE) clean

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)