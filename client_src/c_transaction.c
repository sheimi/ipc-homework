#include <client/c_transaction.h>
#include <env.h>
#include <stdio.h>
#include <lib/request_parser.h>

ClientState status;

void print_info();
char get_choice();
void get_str(char * info, char * result);

static void init_handler();
static void login_handler();
static void register_handler();
static void verified_handler();
static void order_handler();

void start_transaction() {
  status = C_INIT;
  while (true) {
    fprintf(stderr, "Working.....\n");
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
  get_str("username: ", username);
  get_str("password: ", password);

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
  get_str("username: ", username);
  do {
    if (try > 0) {
      fputs("password not the same, try again\n", stdout);
    }
    get_str("password: ", password);
    get_str("repeat password: ", password_r);
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
  char origin[32];
  char terminal[32];
  char * params[2] = {origin, terminal};

  print_info();
  //query the stations
  send_request(QUERY_STATIONS, 0, NULL);
  Response * response = get_response();

  //print data from server
  pch = strtok(response->data, " "); 
  while(pch != NULL) {
    fprintf(stdout, "    %s\n", pch);
    pch = strtok(NULL, " ");
  }

  //get origin and des
  get_str("Your Origin Station :  ", origin);
  get_str("Your Terminal Station :  ", terminal);
  send_request(QUERY_TRAIN, 2, params); 

  response = get_response();
  
  fputs("Available trains : \n", stdout);
  //print data from server
  pch = strtok(response->data, " "); 
  while(pch != NULL) {
    fprintf(stdout, "  train name: %s", pch);
    pch = strtok(NULL, " ");
    fprintf(stdout, "  start station: %s", pch);
    pch = strtok(NULL, " ");
    fprintf(stdout, "  end station: %s\n", pch);
    pch = strtok(NULL, " ");
  }
  
  //origin -> train name;  terminal -> date;
  get_str("train name: ", origin);
  get_str("your date (YYYY-MM-DD) : ", terminal);
  send_request(BUY_IT, 2, params);

  response = get_response();
  if (response->rs == SUCCESS) {
    fputs("Your reservation has been rendered\n", stdout); 
  } else {
    fputs("No more seat for your train on that date\n", stdout); 
  }
  status = C_VERIFIED;
}

void print_info() {
  switch(status) {
    case C_VERIFY_ERROR:
      fputs("Encounter an error when you input your information\n\n", stdout);
    case C_INIT:
      fputs("Welcome To the Ticket Reserve System, Please Choose Your Operation:\n", stdout);
      fputs("    1. Log In\n", stdout);
      fputs("    2. REGISTER\n", stdout);
      fputs("    3. QUIT\n", stdout);
      break;
    case C_LOGIN:
    case C_REGISTER:
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
    default:
      break;
  }
}

char get_choice() {
  fputs("Your Choice Is : ", stdout);
  //purge the stdin stream
  fpurge(stdin);
  char c = getchar();
  return c;
}

void get_str(char * info, char * result) {
  fputs(info, stdout);
  //purge the stdin stream
  fpurge(stdin);
  fscanf(stdin, "%s", result);
}
