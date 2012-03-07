#include <client/c_transaction.h>
#include <env.h>
#include <stdio.h>
#include <lib/request_parser.h>

ClientState status;

void print_info();
char get_choice();

static void init_handler();
static void login_handler();

void start_transaction() {
  status = C_INIT;
  while (true) {
    switch(status) {
      case C_INIT:
        init_handler(); 
        break;
      case C_QUITED:
        send_request(QUIT, 0, NULL);
        return;
      case C_LOGIN:
        login_handler();
        break;
      case C_REGISTER:
        break;
      case C_VERIFIED:
        fprintf(stderr, "verified\n");
        return;
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
  fputs("username: ", stdout);
  fscanf(stdin, "%s", username);
  fputs("password: ", stdout);
  fscanf(stdin, "%s", password); 
  fprintf(stdout, "%s %s\n", username, password);
  params[0] = username;
  params[1] = password;
  send_request(LOGIN, 2, params);
  Response * response = get_response();
  if (response->rs == SUCCESS) {
    status = C_VERIFIED;
  } else {
    status = C_INIT;
  }
}

void print_info() {
  switch(status) {
    case C_INIT:
      fputs("Welcome To the Ticket Reserve System, Please Choose Your Operation:\n", stdout);
      fputs("    1. Log In\n", stdout);
      fputs("    2. REGISTER\n", stdout);
      fputs("    3. QUIT\n", stdout);
      break;
    case C_LOGIN:
      fputs("Please enter your username and password\n", stdout);
      break;
  }
}

char get_choice() {
  fputs("Your Choice Is : ", stdout);
  char c = getchar();
  return c;
}

