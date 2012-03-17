#include <client/c_transaction.h>
#include <env.h>
#include <stdio.h>
#include <lib/request_parser.h>
#include <stdlib.h>

ClientState status;

void print_info();
char get_choice();
void get_str(char * info, char * result);
void print_divider();

static void init_handler();
static void login_handler();
static void register_handler();
static void verified_handler();
static void order_handler();
static void refund_handler();

void start_transaction() {
  status = C_INIT;
  while (true) {
  #ifdef DEBUG
    fprintf(stderr, "Working.....\n");
  #endif
    switch(status) {
      case C_INIT:
      case C_VERIFY_ERROR:
        init_handler(); 
        break;
      case C_QUITED:
        send_request(QUIT, 0, NULL);
        return;
      case C_LOGIN:
        login_handler();
        break;
      case C_REGISTER:
        register_handler();
        break;
      case C_VERIFIED:
        verified_handler();
        break;
      case C_ORDER:
        order_handler();
        break;
      case C_REFUND:
        refund_handler();
      default:
        break;
    }
  }
}

static void init_handler() {
  print_info();
  char c = get_choice();
  switch(c) {
    case '1':
      status = C_LOGIN;
      break;
    case '2':
      status = C_REGISTER;
      break;
    case '3':
      status = C_QUITED;
      break;
  }
}

static void login_handler() {
  char username[30];
  char password[30];
  char * params[2];
  print_info();

  //get the user name and pwd to log in
  print_divider(0);
  get_str("username: ", username);
  get_str("password: ", password);
  print_divider(0);

  params[0] = username;
  params[1] = password;
  send_request(LOGIN, 2, params);
  Response * response = get_response();
  if (response->rs == SUCCESS) {
    status = C_VERIFIED;
  } else {
    status = C_VERIFY_ERROR;
  }
}

static void register_handler() {
  char username[30];
  char password[30];
  char password_r[30];
  char * params[2];
  int try = 0;
  print_info();

  //get the user name and pwd to log in
  print_divider(0);
  get_str("username: ", username);
  do {
    if (try > 0) {
      fputs("password not the same, try again\n", stdout);
      print_divider(0);
    }
    print_divider(0);
    get_str("password: ", password);
    get_str("repeat password: ", password_r);
    print_divider(0);
    try++;
  } while (str_nequal(password, password_r) && try < 3);

  if (str_nequal(password, password_r)) {
    status = C_VERIFY_ERROR;
    return;
  }
  params[0] = username;
  params[1] = password;
  send_request(REGISTER, 2, params);
  Response * response = get_response();
  if (response->rs == SUCCESS) {
    status = C_VERIFIED;
  } else {
    status = C_VERIFY_ERROR;
  }

}

static void verified_handler() {
  print_info();
  char c = get_choice();
  switch(c) {
    case '1':
      status = C_ORDER;
      break;
    case '2':
      status = C_REFUND;
      break;
    case '3':
      status = C_QUITED;
      break;
  }
}

static void order_handler() {
  char * pch;
  char arg1[32];
  char arg2[32];
  char * args[2] = {arg1, arg2};

  print_info();
  //query the stations
  send_request(QUERY_STATIONS, 0, NULL);
  Response * response = get_response();

  //print data from server
  pch = strtok(response->data, " "); 
  fprintf(stdout, "%15s\n", "Station Name");
  while(pch != NULL) {
    fprintf(stdout, "%15s\n", pch);
    pch = strtok(NULL, " ");
  }

  //get origin and des
  print_divider(0);
  get_str("Your Origin Station :  ", arg1);
  get_str("Your Terminal Station :  ", arg2);
  print_divider(0);
  send_request(QUERY_TRAIN, 2, args) ; 

  response = get_response();
  
  fputs("Available trains : \n", stdout);
  //print data from server
  pch = strtok(response->data, " "); 
  fprintf(stdout, "%15s  |  %15s  |  %15s\n", "train name", "start station", "end station");
  print_divider(0);
  while(pch != NULL) {
    fprintf(stdout, "%15s  |  ", pch);
    pch = strtok(NULL, " ");
    fprintf(stdout, "%15s  |  ", pch);
    pch = strtok(NULL, " ");
    fprintf(stdout, "%15s\n", pch);
    pch = strtok(NULL, " ");
  }
  
  //origin -> train name;  terminal -> date;
  print_divider(0);
  get_str("train name: ", arg1);
  get_str("your date (YYYY-MM-DD) : ", arg2);
  print_divider(0);
  send_request(BUY_IT, 2, args);

  response = get_response();
  if (response->rs == SUCCESS) {
    fputs("Your reservation has been rendered\n", stdout); 
  } else {
    fputs("No more seat for your train on that date\n", stdout); 
  }
  status = C_VERIFIED;
}

static void refund_handler() {
  char arg1[32];
  char * pch;
  char * args[1] = {arg1};
  send_request(QUERY_ORDERS, 0, NULL); 
  Response * response = get_response();

  if (response->rs == FAILED) {
    fprintf(stdout, "No more orders\n");   
    print_divider(0);
    status = C_VERIFIED;
    return;
  }

  pch = strtok(response->data, " "); 
  fprintf(stdout, "%15s  |  %15s  |  %25s\n", "order id", "train name", "date");
  print_divider(0);
  while(pch != NULL) {
    fprintf(stdout, "%15s  |  ", pch);
    pch = strtok(NULL, " ");
    fprintf(stdout, "%15s  |  ", pch);
    pch = strtok(NULL, " ");
    fprintf(stdout, "%20s\n", pch);
    pch = strtok(NULL, " ");
  }
  print_divider(0);

  print_divider(0);
  get_str("order your choose (order id or type 0 to quit): ", arg1);
  print_divider(0);
  
  if (atoi(arg1) == 0) {
    status = C_VERIFIED;
    return;
  }

  send_request(REFUND, 1, args);
  response = get_response();

  if (response->rs == SUCCESS) {
    fputs("Your order has been deleted successfully\n", stdout); 
  } else {
    fputs("Encounter an error\n", stdout); 
  }
  
  status = C_VERIFIED;
}

void print_info() {
  fputs("\n\n", stdout);
  switch(status) {
    case C_VERIFY_ERROR:
      fputs("Encounter an error when you input your information\n", stdout);
    case C_INIT:
      fputs("Welcome To the Ticket Reserve System, Please Choose Your Operation:\n", stdout);
      fputs("    1. Log In\n", stdout);
      fputs("    2. REGISTER\n", stdout);
      fputs("    3. QUIT\n", stdout);
      break;
    case C_LOGIN:
    case C_REGISTER:
      print_divider(0);
      fputs("Please enter your username and password\n", stdout);
      break;
    case C_VERIFIED:
      fputs("Welcome Back..., Please Choose Your Operation...: \n", stdout);
      fputs("    1. Order Ticket.\n", stdout);
      fputs("    2. Refund.\n", stdout);
      fputs("    3. QUIT\n", stdout);
      break;
    case C_ORDER:
      fputs("Here is the available station, Please choose your origin station and terminal station\n", stdout);
      break;
    case C_REFUND:
      fputs("Here is your orders, please choose one to refund: \n", stdout);
      break;
    default:
      break;
  }
}

char get_choice() {
  print_divider(0);
  fputs("Your Choice Is : ", stdout);
  //purge the stdin stream
  fpurge(stdin);
  char c = getchar();
  print_divider(0);
  return c;
}

void get_str(char * info, char * result) {
  fputs(info, stdout);
  //purge the stdin stream
  fpurge(stdin);
  fscanf(stdin, "%s", result);
}

void print_divider(int k) {
  int num = 50;
  int i;
  if (k != 0) {
    num = k;
  }
  for (i = 0; i < num; i++) {
    fputc('-', stdout);    
  }
  fputc('\n', stdout);
}
