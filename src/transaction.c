#include <server/transaction.h>
#include <lib/request_parser.h>
#include <stdio.h>
#include <server/db.h>

typedef enum _server_state {
  INIT,
  VERIFIED,
  IDLE,
} ServerState;

ServerState state;

static void login(Request * request);
static void register_u(Request * request);

int start_transaction() {
  state = INIT;
  connect_db();
  while (true) {
    Request * request = get_request();
    switch(request->cmd) {
      case LOGIN:
        login(request);
        break;
      case REGISTER:
        register_u(request);
        break;
      case QUIT:
        fprintf(stderr, "QUIT\n");
        state = IDLE;
        close_db();
        return 0;
    }
  }
  return 0;
}

/*
 *  the transaction methods
 */

static void login(Request * request) {
  bool result = check_user(request->params[0], request->params[1]);
  response.param_num = 0;
  if (result) {
    response.rs = SUCCESS;
    state = VERIFIED; 
  } else {
    response.rs = FAILED;
  }
  send_response();
}

static void register_u(Request * request) {
  bool result = register_user(request->params[0], request->params[1]);
  response.param_num = 0;
  if (result) {
    response.rs = SUCCESS;
    state = VERIFIED; 
  } else {
    response.rs = FAILED;
  }
  send_response();
}
