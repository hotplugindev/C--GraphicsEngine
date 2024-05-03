CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-lGL -lGLU -lglut -lglfw -lm
SRCDIR=src
TARGETDIR=target
SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(patsubst $(SRCDIR)/%.c,$(TARGETDIR)/%.o,$(SOURCES))
EXECUTABLE=$(TARGETDIR)/main

all: clean $(EXECUTABLE) copydeps

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(TARGETDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

copydeps:
	cp -r $(SRCDIR)/sources/* $(TARGETDIR)

clean:
	rm -rf $(TARGETDIR)/*
