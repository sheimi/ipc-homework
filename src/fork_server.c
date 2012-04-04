#include <socket/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <lib/request_parser.h>
#include <server/transaction.h>
#include <lib/lock.h>

static void sig_int(int signo); 

int main(int argc, char * argv[]) {
  int listenfd;
  int connfd;
  
  listenfd = init_server();
  signal_wrapper(SIGINT, sig_int);

  //to lock the log file
  lock_init(LOG_LOCK);
  
  while (true) {
    connfd = wait_client(listenfd);
    pid_t p = fork_wrapper();
    if (p == 0) {
      start_transaction();
      exit(0);
    }
    close_wrapper(connfd);
  }
  return 0;
}

static void sig_int(int signo) {
  while (wait(NULL) > 0); 
  exit(0); 
}

