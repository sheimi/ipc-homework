#ifndef FIFO_H
#define FIFO_H

#include <env.h>
#include <lib/error.h>
#include <lib/wrapper.h>

#define SERV_FIFO "/tmp/ticket/server.fifo"
#define FIFO_MODE 0777
#define INFO_MSG 16 
#define NAME_LEN 32
#define CHILD_CHANNAL  "/tmp/ticket/fifo.%d"

//server side functon

/*
 *  to init the fifo server, including:
 *    open the public fifo
 */
int init_server();

/*
 *  waiting for the connect from the server, including:
 *    wait for the connection
 *    dup the fifo descriptors to two files 
 *
 */
int wait_client();

//client function
/*
 *  to init the fifo client, including:
 *    try to connect to the fifo server
 *    dup the fifo descriptors to two files
 *
 */
int init_client();

/*
 *  to close the fifo client, including:
 *    try to close to fifo descriptors
 */
int close_client();

#endif
