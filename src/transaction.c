#include <server/transaction.h>
#include <lib/request_parser.h>
#include <stdio.h>

typedef enum _server_state {
  INIT,
  IDLE,
} ServerState;

ServerState state;

int start_transaction() {
  state = INIT;
  while (true) {
    Request * request = get_request();
    switch(request->cmd) {
      case LOGIN:
        fprintf(stderr, "LOGIN\n");
        break;
      case REGISTER:
        fprintf(stderr, "REGISTER\n");
        break;
      case QUIT:
        fprintf(stderr, "QUIT\n");
        state = IDLE;
        return 0;
    }
    response.rs = LOGIN_R;
    response.param_num = 0;
    send_response();
  }
  return 0;
}
