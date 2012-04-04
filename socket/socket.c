#include <socket/socket.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <lib/readline.h>
#include <lib/request_parser.h>
#include <sys/socket.h>

socklen_t addrlen;

int init_server() {
  int listenfd;
  listenfd = tcp_listen(HOST, PORT, &addrlen);
  readport = NULL;
  writeport = NULL;
  return listenfd;
}

int wait_client(int listenfd) {
  socklen_t clilen;
  struct socketaddr * cliaddr;

  if (readport) {
    int fno = fileno(readport);
    close(fno);
  }

  cliaddr = (struct socketaddr *)(malloc(addrlen));
  clilen = addrlen;

  int connfd = accept(listenfd, cliaddr, &clilen);

  readport = fdopen(connfd, "r");
  writeport = fdopen(connfd, "w");
  return connfd;
} 


int init_client() {
  int connfd = tcp_connect(HOST, PORT);
  readport = fdopen(connfd, "r");
  writeport = fdopen(connfd, "w");
  return 0;
}

int close_client() {
  fclose(readport);
  fclose(writeport);
  return 0;
}
