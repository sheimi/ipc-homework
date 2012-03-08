#include <lib/wrapper.h>
#include <lib/error.h>

#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <sys/socket.h>
#include <netdb.h>

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

int tcp_listen(const char * host, const char * serv, socklen_t * addrlenp) {
  int       listenfd, n;
  const int   on = 1;
  struct addrinfo hints, *res, *ressave;

  bzero(&hints, sizeof(struct addrinfo));
  hints.ai_flags = AI_PASSIVE;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
    err_quit("socket err");
  ressave = res;

  do {
    listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (listenfd < 0)
      continue;   /*  error, try next one */

    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
      break;      /*  success */

    close(listenfd);  /*  bind error, close and try next one */
  } while ( (res = res->ai_next) != NULL);

  if (res == NULL)  /*  errno from final socket() or bind() */
    err_quit("socket err");

  listen(listenfd, 1024);

  if (addrlenp)
    *addrlenp = res->ai_addrlen;  /*  return size of protocol address*/ 
  freeaddrinfo(ressave);
  return(listenfd);
}


int tcp_connect(const char *host, const char *serv) {
  int       sockfd, n;
  struct addrinfo hints, *res, *ressave;

  bzero(&hints, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if ( (n = getaddrinfo(host, serv, &hints, &res)) != 0)
    err_quit("tcp_connect error for");
  ressave = res;

  do {
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0)
      continue; 

    if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
      break;    

    close_wrapper(sockfd);  
  } while ( (res = res->ai_next) != NULL);

  if (res == NULL)  
    err_quit("tcp_connect error");

  freeaddrinfo(ressave);

  return sockfd;
} 
