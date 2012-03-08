#ifndef SOCKET_H
#define SOCKET_H

#include <env.h>
#include <lib/error.h>
#include <lib/wrapper.h>

#define PORT "2000" 
#define HOST "localhost"

//server side functon

/*
 *  to init the socket server, including:
 *  listen socket
 */
int init_server();

/*
 *  waiting for the connect from the server, including:
 *    wait for the connection
 *    dup the socket descriptors to two files 
 *
 */
int wait_client();

//client function
/*
 *  to init the socket client, including:
 *    try to connect to the socket server
 *    dup the socket escriptors to two files
 *
 */
int init_client();

/*
 *  to close the socket client, including:
 *    try to close to socket descriptors
 */
int close_client();

#endif
