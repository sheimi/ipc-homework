#ifndef READLINE_H
#define READLINE_H

#include <env.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <lib/error.h>

#define MAX_SIZE 1024

ssize_t readline_wrapper(int fd, void * ptr, size_t maxlen);

#endif
