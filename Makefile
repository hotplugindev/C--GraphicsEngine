CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-lGL -lGLU -lglut -lglfw -lm
SRCDIR=src
TARGETDIR=target
SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(patsubst $(SRCDIR)/%.c,$(TARGETDIR)/%.o,$(SOURCES))
EXECUTABLE=$(TARGETDIR)/main

all: clean $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(TARGETDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
