#include <lib/error.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static void err_all(const char * msg);

void err_msg(const char * msg) {
  err_all(msg);
}

void err_quit(const char * msg) {
  err_all(msg);
  exit(1);
}

static void err_all(const char * msg) {
  fputs(msg, stderr);
  fputs("\n", stderr);
  fflush(stderr);
}
