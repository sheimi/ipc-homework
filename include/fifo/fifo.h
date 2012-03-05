#ifndef FIFO_H
#define FIFO_H

#include <env.h>
#include <lib/error.h>
#include <lib/wrapper.h>

#define SERV_FIFO "/tmp/ticket/server.fifo"
#define FIFO_MODE 0777
#define INFO_MSG 16 
#define NAME_LEN 64 
#define SERVER_WRITE "/tmp/ticket/fifow.%d"
#define SERVER_READ  "/tmp/ticket/fifor.%d"
#define CLIENT_READ  "/tmp/ticket/fifow.%d"
#define CLIENT_WRITE "/tmp/ticket/fifor.%d"

//server functon
int init_server();
int wait_client();

//client function
int init_client();

#endif
