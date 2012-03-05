#include <fifo/fifo.h>
#include <stdio.h>
#include <lib/request_parser.h>

int main(int argc, char * argv[]) {
  char buf[32];
  init_client();
  fprintf(stdout, "sendwangsend\n");
  fflush(stdout);
  fscanf(stdin, "%s", buf);
  fprintf(stderr, "%s\n", buf); 
  fprintf(stderr, "closed.....\n");
  request.cmd = LOGIN;
  request.param_num = 2;
  request.params[0] = "hello";
  request.params[1] = "world";
  send_request();
  close_client();
  return 0;
}
