#include <lib/readline.h>
#include <stdio.h>

static int read_cnt;
static char * read_ptr;
static char read_buf[MAX_SIZE];

static ssize_t my_read(int fd, char * ptr, size_t maxlen) {
  if (maxlen == 0) {
    maxlen = sizeof(read_buf);
  }
  if (read_cnt <= 0) {
  again:
    if ((read_cnt = read(fd, read_buf, maxlen)) < 0) {
      if (errno == EINTR)
        goto again;
      return -1;
    } else if (read_cnt == 0) {
      return 0;
    }
    read_ptr = read_buf;
  }
  read_cnt--;
  *ptr = *read_ptr;
  read_ptr++;
  return 1;
}

ssize_t readline(int fd, void * vptr, size_t maxlen) {
  ssize_t n, rc;
  char c;
  char * ptr;
  ptr = vptr;
  for (n = 1; n < maxlen; n++) {
    if ((rc = my_read(fd, &c, 0)) == 1) {
      *ptr = c;
      ptr++;
      if (c == '\n')
        break;
      } else if (rc == 0) {
      *ptr = 0;
      return n - 1;
    } else {
      return -1;
    }
  }
  *ptr = 0;
  return n;
}

ssize_t readline_nobuf(int fd, void * vptr, size_t maxlen) {
  ssize_t n, rc;
  char c;
  char * ptr;
  
  read_cnt = 0;
  ptr = vptr;
  for (n = 1; n < maxlen+1; n++) {
    if ((rc = my_read(fd, &c, maxlen)) == 1) {
      *ptr = c;
      ptr++;
      if (c == '\n')
        break;
      } else if (rc == 0) {
      *ptr = 0;
      return n - 1;
    } else {
      return -1;
    }
  }
  *ptr = 0;
  read_cnt = 0;
  return n;
}

ssize_t readline_wrapper(int fd, void * ptr, size_t maxlen) {
  ssize_t n;
  if ((n = readline(fd, ptr, maxlen)) < 0)
    err_quit("readline error");
  return n;
}

ssize_t readline_nobuf_wrapper(int fd, void * ptr, size_t maxlen) {
  ssize_t n;
  if ((n = readline_nobuf(fd, ptr, maxlen)) < 0)
    err_quit("readline error");
  return n;

}
