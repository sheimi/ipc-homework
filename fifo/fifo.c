#include <fifo/fifo.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <lib/readline.h>
#include <lib/request_parser.h>

static int dummyfd;

int init_server() {
  int readfifo;
  mkfifo_wrapper(SERV_FIFO, FIFO_MODE);
  readfifo = open_wrapper(SERV_FIFO, O_RDONLY, 0); 
  //readfifo = open_wrapper(SERV_FIFO, O_RDONLY | O_NONBLOCK, 0); 
  dummyfd = open_wrapper(SERV_FIFO, O_WRONLY, 0);
  readport = NULL;
  writeport = NULL;
  return readfifo;
}

int wait_client(int fd) {
  char buf[INFO_MSG];

  char name_r[NAME_LEN];
  char name_w[NAME_LEN];

  int r;

  if (readport || writeport) {
    fclose(readport);
    fclose(writeport);
  }
  
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
  writeport = fopen(name_w, "w");

  //set confirm
  fprintf(stderr, "request recieved...\n");
  fprintf(writeport, "%ld\n", (long)getpid()); 
  fflush(writeport);

  readport = fopen(name_r, "r");
  
  //built
  fscanf(readport, "%s", buf);
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
  readport = fopen(name_r, "r");
  fscanf(readport, "%s", buf);
  fprintf(stderr, "receive confirmed...\n");
  
  //build channel
  pid = atoi(buf);
  sprintf(name_w, CHILD_CHANNAL, pid);
  writeport = fopen(name_w, "w"); 

  fprintf(writeport, "confirm\n");
  fflush(writeport);
  fprintf(stderr, "confirm sent\n");
  
  return 0;
}

int close_client() {
  fclose(readport);
  fclose(writeport);
  return 0;
}
