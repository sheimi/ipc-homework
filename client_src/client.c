#include <fifo/fifo.h>
#include <stdio.h>
#include <lib/request_parser.h>

int main(int argc, char * argv[]) {
  char buf[32];
  init_client();

  request.cmd = LOGIN;
  request.param_num = 0;
  send_request();

  get_response();
  request.cmd = REGISTER;
  request.param_num = 0;
  send_request();
  get_response();

  request.cmd = QUIT;
  request.param_num = 0;
  send_request();

  close_client();
  fprintf(stderr, "closed.....\n");
  return 0;
}
