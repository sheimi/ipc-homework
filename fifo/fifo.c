#include <fifo/fifo.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <lib/readline.h>

int dummyfd;

int init_server() {
  int readfifo;
  mkfifo_wrapper(SERV_FIFO, FIFO_MODE);
  readfifo = open_wrapper(SERV_FIFO, O_RDONLY, 0); 
  //readfifo = open_wrapper(SERV_FIFO, O_RDONLY | O_NONBLOCK, 0); 
  dummyfd = open_wrapper(SERV_FIFO, O_WRONLY, 0);
  return readfifo;
}

int wait_client(int fd) {
  int writefifo;
  int readfifo;
  char buf[1024];
  char name_r[30];
  char name_w[30];
  fprintf(stderr, "process %ld inner waiting\n", (long)getpid());
  int r;
  r = readline(fd, buf, 1024); 

  fprintf(stderr, "\n%s  %d\n", buf, r);

  fprintf(stderr, "process %ld inner running\n", (long)getpid());
  int pid = atoi(buf);
  sprintf(name_w, "/tmp/ticket/fifow.%d", pid);
  sprintf(name_r, "/tmp/ticket/fifor.%d", pid);
  mkfifo_wrapper(name_w, FIFO_MODE);
  mkfifo_wrapper(name_r, FIFO_MODE);
  writefifo = open_wrapper(name_w, O_WRONLY, 0);
  readfifo = open_wrapper(name_r, O_RDONLY, 0);
  close_wrapper(0);
  close_wrapper(1);
  dup2_wrapper(readfifo, STDIN_FILENO);
  dup2_wrapper(writefifo, STDOUT_FILENO);
  close(readfifo);
  close(writefifo);
  close_wrapper(0);
  close_wrapper(1);
  return 0;
} 
