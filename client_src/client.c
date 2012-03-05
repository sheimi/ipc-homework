#include <fifo/fifo.h>
#include <stdio.h>

int main(int argc, char * argv[]) {
  init_client();
  fprintf(stdout, "sendwangsend\n");
  fflush(stdout);
  char buf[32];
  fscanf(stdin, "%s", buf);
  fprintf(stderr, "%s\n", buf); 
  fprintf(stderr, "pausing.....");
  pause();
}
