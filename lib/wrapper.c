#include <lib/wrapper.h>
#include <lib/error.h>

#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>

pid_t fork_wrapper() {
  pid_t pid;
  if ((pid = fork()) < 0) {
    err_quit("Fork Error");
  }
  return pid;
}

void mkfifo_wrapper(const char * path, mode_t mode) {
  if ((mkfifo(path, mode) < 0) && (errno != EEXIST))
    err_quit("can' create fifo");
}

int open_wrapper(const char * path, int oflag, mode_t mode) {
  int fd;
  if ((fd = open(path, oflag, mode)) == -1)
    err_quit("open file error");
  return fd;
}

void close_wrapper(int fd) {
  if (close(fd) == -1)
    err_quit("close file error");
}

ssize_t read_wrapper(int fd, void * ptr, size_t nbytes) {
  ssize_t n;
  //if ((n = read(fd, ptr, nbytes)) == -1)
    //err_quit("read error");
  return n;
}

void dup2_wrapper(int fd1, int fd2) {
  if (dup2(fd1, fd2) == -1)
    err_quit("dup error");
}

sigfunc signal_wrapper(int signo, sigfunc func) {
  struct sigaction act, oact;
  act.sa_handler = func;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  if (sigaction(signo, &act, &oact) < 0)
    err_quit("signal error");
  return oact.sa_handler;
}
