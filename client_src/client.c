#include <fifo/fifo.h>
#include <stdio.h>
#include <lib/request_parser.h>

int main(int argc, char * argv[]) {
  init_client();

  request.cmd = REGISTER;
  request.param_num = 2;
  request.params[0] = "shaymin";
  request.params[1] = "zhang";
  send_request();
  Response * response = get_response();
  fprintf(stderr, "%d\n", response->rs);

  close_client();
  fprintf(stderr, "closed.....\n");
  return 0;
}
