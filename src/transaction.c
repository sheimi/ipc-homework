#include <server/transaction.h>
#include <lib/request_parser.h>
#include <stdio.h>
#include <server/db.h>

#define LOG_FILE "db/ticket.log"

FILE * log_file;

typedef enum _server_state {
  INIT,
  VERIFIED,
  IDLE,
} ServerState;

static ServerState state;

static void login(Request * request);
static void register_u(Request * request);
static void query_stations();
static void query_train(Request * request); 
static void buy_it(Request * request);
static void query_orders();
static void refund_orders(Request * request);

int start_transaction() {

  log_file = fopen(LOG_FILE, "a");

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
        fclose(log_file);
        return 0;
      case QUERY_STATIONS:
        query_stations();
        break;
      case QUERY_TRAIN:
        query_train(request);
        break;
      case BUY_IT:
        buy_it(request);
        break;
      case QUERY_ORDERS:
        query_orders();
        break;
      case REFUND:
        refund_orders(request);
        break;
      default:
        break;
    }
  }
  return 0;
}

/*
 *  the transaction methods
 */

char username[30];

static void login(Request * request) {
  bool result = check_user(request->params[0], request->params[1]);
  ResponseStatus rs;
  if (result) {
    strcpy(username, request->params[0]);
    rs = SUCCESS;
    state = VERIFIED; 
  } else {
    rs = FAILED;
  }
  send_response(rs, 0, NULL);
}

static void register_u(Request * request) {
  bool result = register_user(request->params[0], request->params[1]);
  ResponseStatus rs;
  if (result) {
    strcpy(username, request->params[0]);
    rs = SUCCESS;
    state = VERIFIED; 
  } else {
    rs = FAILED;
  }
  send_response(rs, 0, NULL);
}

static void query_stations() {
  char ** dbr = 0;
  int row, column;
  char buf[4096];
  char * p = buf;
  int i;
  row = 0;
  column = 0;
  query_stations_db(&dbr, &row, &column); 
  for (i = column; i < (row + 1) * column; i++) {
    sprintf(p, "%s ", dbr[i]); 
    p += strlen(dbr[i]) + 1;
  } 
  send_response(SUCCESS, strlen(buf) + 1, buf);
  release_dbr(dbr);
}

static void query_train(Request * request) {
  char ** dbr = 0;
  int row, column;
  char buf[4096];
  char * p = buf;
  int i;
  query_train_db(&dbr, &row, &column, request->params[0], request->params[1]);  
  for (i = column; i < (row + 1) * column; i++) {
    sprintf(p, "%s ", dbr[i]); 
    p += strlen(dbr[i]) + 1;
  } 
  send_response(SUCCESS, strlen(buf) + 1, buf);
  release_dbr(dbr);
}


static void buy_it(Request * request) {
  int rs;
  bool result = buy_ticket_db(request->params[0], request->params[1]);
  if (result) {
    fprintf(log_file, "order: %s, %s, %s\n", username, request->params[0], request->params[1]); 
    rs = SUCCESS;
  } else {
    rs = FAILED;
  }
  send_response(rs, 0, NULL);
}

static void query_orders() {
  char ** dbr = 0;
  int row, column;
  char buf[4096];
  char * p = buf;
  int i;

  query_orders_db(&dbr, &row, &column);
  if (row > 0) {
    for (i = column; i < (row + 1) * column; i++) {
      sprintf(p, "%s ", dbr[i]); 
      p += strlen(dbr[i]) + 1;
    } 
    send_response(SUCCESS, strlen(buf) + 1, buf);
  } else {
    send_response(FAILED, 0, 0);
  }
  release_dbr(dbr);
}

static void refund_orders(Request * request) {
  int rs;
  bool result = delete_order_db(request->params[0]);
  if (result) {
    fprintf(log_file, "refund: %s, %s\n", username, request->params[0]); 
    rs = SUCCESS;
  } else {
    rs = FAILED;
  }
  send_response(rs, 0, NULL);
}
