#ifndef WRAPPER_H
#define WRAPPER_H

#include "env.h"
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>

pid_t fork_wrapper();
void mkfifo_wrapper(const char * path, mode_t mode);
int open_wrapper(const char * path, int oflag, mode_t mode); 
void close_wrapper(int fd);
ssize_t read_wrapper(int fd, void * ptr, size_t nbytes);
void dup2_wrapper(int fd1, int fd2); 

typedef void (*sigfunc)(int signo);
sigfunc signal_wrapper(int signo, sigfunc func); 

int tcp_listen(const char * host, const char * serv, socklen_t * addrlenp);
int tcp_connect(const char *host, const char *serv); 
  
#endif

