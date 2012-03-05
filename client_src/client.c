#include <fifo/fifo.h>
#include <stdio.h>

int main(int argc, char * argv[]) {
  char buf[32];
  init_client();
  fprintf(stdout, "sendwangsend\n");
  fflush(stdout);
  fscanf(stdin, "%s", buf);
  fprintf(stderr, "%s\n", buf); 
  fprintf(stderr, "closed.....\n");
  close_client();
  return 0;
}
