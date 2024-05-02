 CC = g++

  # compiler flags:
  #  -g     - this flag adds debugging information to the executable file
  #  -Wall  - this flag is used to turn on most compiler warnings
  CFLAGS  = -g -Wall

  # The build target
  TARGET = target/main

  all: $(TARGET)

  $(TARGET): $(TARGET).c
                $(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

  clean:
                $(RM) $(TARGET)
