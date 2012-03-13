#ifdef FIFO
  #include <fifo/fifo.h>
#else
  #include <socket/socket.h>
#endif 
#include <stdio.h>
#include <lib/request_parser.h>
#include <client/c_transaction.h>

int main(int argc, char * argv[]) {
  init_client();
  start_transaction();
  close_client();
  fprintf(stderr, "closed.....\n");
  return 0;
}
