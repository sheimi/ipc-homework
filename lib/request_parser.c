#include <lib/request_parser.h>
#include <stdio.h>
#include <string.h>

//server side function

static Request request;
static Response response;

FILE * readport;
FILE * writeport;

#define BUFSIZE 1024
char buf[BUFSIZE];

Request * get_request() {
  char * ptr = buf;
  int i; 
  int cmd;
  
  memset(buf, 0, sizeof(buf));

  fscanf(readport, "%d", &cmd); 
  request.cmd = (RequestCMD)cmd;
  fscanf(readport, "%d", &request.param_num);
  for (i = 0; i < request.param_num; i++) {
    request.params[i] = ptr;
    fscanf(readport, "%s", ptr);
    ptr = ptr + strlen(ptr) + 1;
  }
  return &request;
}

int send_response(ResponseStatus rs, int num, char * params[]) {
  int i;
  fprintf(writeport, "%d %d ", rs, num);
  for (i = 0; i < num; i++) {
    fprintf(writeport, "%s ", params[i]);
  }
  fflush(writeport);
  return 0;
}

//client side function

int send_request(RequestCMD cmd, int num, char * params[]) {
  int i;
  fprintf(writeport, "%d %d ", cmd, num);
  for (i = 0; i < num; i++) {
    fprintf(writeport, "%s ", params[i]);
  }
  fflush(writeport);
  return 0;
}


Response * get_response() {
  char * ptr = buf;
  int i; 
  int rs;
  memset(buf, 0, sizeof(buf));
  fscanf(readport, "%d", &rs); 
  response.rs= (ResponseStatus)rs;
  fscanf(readport, "%d", &response.param_num);
  for (i = 0; i < response.param_num; i++) {
    response.params[i] = ptr;
    fscanf(readport, "%s", ptr);
    ptr = ptr + strlen(ptr) + 1;
  }
  return &response;
}

