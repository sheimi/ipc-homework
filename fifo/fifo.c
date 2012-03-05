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
  char buf[INFO_MSG];
  char name_r[NAME_LEN];
  char name_w[NAME_LEN];
  int r;

  fprintf(stderr, "process %ld waiting\n", (long)getpid());
  r = readline_nobuf_wrapper(fd, buf, INFO_MSG); 
  fprintf(stderr, "process %ld running\n", (long)getpid());
  fprintf(stderr, "%s  %d %ld\n", buf, r, (long)getpid());
  buf[r-1] = '\0';
  int pid = atoi(buf);
  sprintf(name_w, SERVER_WRITE, pid);
  sprintf(name_r, SERVER_READ, pid);
  mkfifo_wrapper(name_w, FIFO_MODE);
  mkfifo_wrapper(name_r, FIFO_MODE);
  writefifo = open_wrapper(name_w, O_WRONLY, 0);
  readfifo = open_wrapper(name_r, O_RDONLY, 0);
  close_wrapper(0);
  close_wrapper(1);
  dup2_wrapper(readfifo, STDIN_FILENO);
  dup2_wrapper(writefifo, STDOUT_FILENO);
  close_wrapper(readfifo);
  close_wrapper(writefifo);
  sleep(1);
  return 0;
} 

int init_client() {
  char buf[INFO_MSG];
  char name_r[NAME_LEN];
  char name_w[NAME_LEN];
  int readfifo;
  int writefifo = open_wrapper(SERV_FIFO, O_WRONLY, 0);
  pid_t pid = getpid();
  sprintf(name_r, CLIENT_READ, pid);
  sprintf(name_w, CLIENT_WRITE, pid);
  
  sprintf(buf, "%ld\n", (long)pid);
  write(writefifo, buf, INFO_MSG); 
  mkfifo_wrapper(name_w, FIFO_MODE);
  mkfifo_wrapper(name_r, FIFO_MODE);
  close_wrapper(writefifo); 

  readfifo = open_wrapper(name_r, O_RDONLY, 0);
  writefifo = open_wrapper(name_w, O_WRONLY, 0);

  close(0);
  close(1);
  dup2_wrapper(readfifo, STDIN_FILENO);
  dup2_wrapper(writefifo, STDOUT_FILENO);
  close_wrapper(readfifo);
  close_wrapper(writefifo);
}
