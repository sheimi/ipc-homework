CC=gcc
LIB_SRC=lib
INC=include
CFLAGS=-I$(INC) -Wall -c 

SERVER_DIR=src
CLIENT_DIR=client_src
LIB_DIR=lib
FIFO_DIR=fifo

SERVER_OBJS=$(LIB_DIR)/error.o $(LIB_DIR)/wrapper.o $(FIFO_DIR)/fifo.o $(SERVER_DIR)/server.o $(LIB_DIR)/readline.o $(LIB_DIR)/request_parser.o $(SERVER_DIR)/transaction.o $(SERVER_DIR)/db.o
CLIENT_OBJS=$(LIB_DIR)/error.o $(LIB_DIR)/wrapper.o $(FIFO_DIR)/fifo.o $(CLIENT_DIR)/client.o $(LIB_DIR)/readline.o $(LIB_DIR)/request_parser.o $(CLIENT_DIR)/c_transaction.o
STARGET=server
CTARGET=client
ifneq ($(DEBUG),)
	CFLAGS += -g -DDEBUG
else
	CFLAGS += -O2
endif

all: clean server client

server: $(SERVER_OBJS)
	$(CC) $(SERVER_OBJS) -o $(STARGET) -L /usr/lib/sqlite3 -lsqlite3

client: $(CLIENT_OBJS)
	$(CC) $(CLIENT_OBJS) -o $(CTARGET)

server.o: $(SERVER_DIR)/server.c
	$(CC) $(CFLAGS) $< -o $(SERVER_DIR)/server.o

client.o: $(CLIENT_DIR)/client.c
	$(CC) $(CFLAGS) $< -o $(CLIENT_DIR)/client.o

fifo.o: $(FIFO_DIR)/fifo.c
	$(CC) $(CFLAGS) $< -o $(FIFO_DIR)/fifo.o

error.o: $(LIB_DIR)/error.c
	$(CC) $(CFLAGS) $< -o $(LIB_DIR)/error.o

wrapper.o: $(LIB_DIR)/wrapper.c
	$(CC) $(CFLAGS) $< -o $(LIB_DIR)/wrapper.o

readline.o: $(LIB_DIR)/readline.c
	$(CC) $(CFLAGS) $< -o $(LIB_DIR)/readline.o

request_parser.o: $(LIB_DIR)/request_parser.c
	$(CC) $(CFLAGS) $< -o $(LIB_DIR)/request_parser.o

transaction.o: $(SERVER_DIR)/transaction.c
	$(CC) $(CFLAGS) $< -o $(SERVER_DIR)/transaction.o

db.o: $(SERVER_DIR)/db.c
	$(CC) $(CFLAGS) $< -o $(SERVER_DIR)/db.o

c_transaction.o: $(CLIENT_DIR)/c_transaction.o
	$(CC) $(CFLAGS) $< -o $(CLIENT_DIR)/c_transaction.o

clean:
	rm -f *.o
	rm -f $(SERVER_DIR)/*.o
	rm -f $(CLIENT_DIR)/*.o
	rm -f $(FIFO_DIR)/*.o
	rm -f $(LIB_DIR)/*.o
	rm -f server
	rm -f client
