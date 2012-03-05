#ifndef FIFO_H
#define FIFO_H

#include <env.h>
#include <lib/error.h>
#include <lib/wrapper.h>

#define SERV_FIFO "/tmp/ticket/server.fifo"
#define FIFO_MODE 0777

//server functon
int init_server();
int wait_client();

#endif
