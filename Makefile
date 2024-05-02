CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-lGL -lGLU -lglut -lglfw -lm
SOURCES=src/main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=target/main

all: clean $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
