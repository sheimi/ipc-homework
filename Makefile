CC=gcc
LIB_SRC=lib
INC=include
CFLAGS=-I$(INC) -Wall -c
OBJS=error.o wrapper.o fifo.o server.o readline.o
TARGET=server
ifneq ($(DEBUG),)
	CFLAGS += -g -DDEBUG
else
	CFLAGS += -O2
endif

all: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

server.o: src/server.c
	$(CC) $(CFLAGS) $<

fifo.o: fifo/fifo.c
	$(CC) $(CFLAGS) $<

error.o: lib/error.c
	$(CC) $(CFLAGS) $<

wrapper.o: lib/wrapper.c
	$(CC) $(CFLAGS) $<

readline.o: lib/readline.c
	$(CC) $(CFLAGS) $<


clean:
	rm -f *.o
	rm -f server
