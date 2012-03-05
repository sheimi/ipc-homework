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
  
  sprintf(name_r, CHILD_CHANNAL, (int)getpid());
  mkfifo_wrapper(name_r, FIFO_MODE);

  //waiting for request
  fprintf(stderr, "process %ld waiting\n", (long)getpid());
  r = readline_nobuf_wrapper(fd, buf, INFO_MSG); 
  fprintf(stderr, "process %ld running\n", (long)getpid());

  buf[r-1] = '\0';
  int pid = atoi(buf);

  //dup 
  sprintf(name_w, CHILD_CHANNAL, pid);
  mkfifo_wrapper(name_w, FIFO_MODE);
  writefifo = open_wrapper(name_w, O_WRONLY, 0);
  close_wrapper(1);
  dup2_wrapper(writefifo, STDOUT_FILENO);
  close_wrapper(writefifo);

  //set confirm
  fprintf(stderr, "request recieved...\n");
  fprintf(stdout, "%ld\n", (long)getpid()); 
  fflush(stdout);

  readfifo = open_wrapper(name_r, O_RDONLY, 0);
  close_wrapper(0);
  dup2_wrapper(readfifo, STDIN_FILENO);
  close_wrapper(readfifo);
  
  //built
  fscanf(stdin, "%s", buf);
  fprintf(stderr, "connection built ...\n");

  return 0;
} 

int init_client() {
  char buf[INFO_MSG];
  char name_r[NAME_LEN];
  char name_w[NAME_LEN];

  //send request
  int writefifo = open_wrapper(SERV_FIFO, O_WRONLY, 0);
  int pid = (int)getpid();
  sprintf(buf, "%d\n", pid);
  write(writefifo, buf, INFO_MSG); 
  close_wrapper(writefifo); 

  //wait for confirm
  sprintf(name_r, CHILD_CHANNAL, pid);
  mkfifo_wrapper(name_r, FIFO_MODE);
  int readfifo = open_wrapper(name_r, O_RDONLY, 0);
  close_wrapper(0);
  dup2_wrapper(readfifo, STDIN_FILENO);
  fscanf(stdin, "%s", buf);
  fprintf(stderr, "receive confirmed...\n");
  close_wrapper(readfifo);
  
  //build channel
  pid = atoi(buf);
  sprintf(name_w, CHILD_CHANNAL, pid);
  writefifo = open_wrapper(name_w, O_WRONLY, 0);
  close_wrapper(1);
  dup2_wrapper(writefifo, STDOUT_FILENO);
  close_wrapper(writefifo);

  fprintf(stdout, "confirm\n");
  fflush(stdout);
  
  return 0;
}

int close_client() {
  close_wrapper(0);
  close_wrapper(1);
  return 0;
}
