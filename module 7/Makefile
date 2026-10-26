CC = cc
CFLAGS = -Wall -Wextra -std=c11

# Homebrew installs gdbm in its own directory on Mac.
GDBM_PREFIX := $(shell brew --prefix gdbm 2>/dev/null)
CPPFLAGS = -I$(GDBM_PREFIX)/include
LDFLAGS = -L$(GDBM_PREFIX)/lib
LDLIBS = -lgdbm

TARGET = calendar
OBJECTS = main.o calendar.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJECTS) $(LDLIBS)

main.o: main.c calendar.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c main.c

calendar.o: calendar.c calendar.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c calendar.c

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
