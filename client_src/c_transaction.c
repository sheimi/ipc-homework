#include <client/c_transaction.h>
#include <env.h>
#include <stdio.h>

ClientState status;

void print_info();
char get_choice();

void start_transaction() {
  status = C_INIT;
  while (true) {
    print_info();
  }
}

void print_info() {
  switch(status) {
    case C_INIT:
      fputs("Welcome To the Ticket Reserve System, Please Choose Your Operation:\n", stderr);
      fputs("    1. Log In\n", stderr);
      fputs("    2. REGISTER\n", stderr);
      fputs("Your Choice Is : ", stderr);
      break;
  }
}

char get_choice() {
  return 0;
}
