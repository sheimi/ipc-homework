#include <lib/request_parser.h>
#include <stdio.h>
#include <string.h>

//server side function

Request request;
Response response;

#define BUFSIZE 1024
char buf[BUFSIZE];

Request * get_request() {
  char * ptr = buf;
  int i; 
  int cmd;
  
  memset(buf, 0, sizeof(buf));

  fscanf(stdin, "%d", &cmd); 
  request.cmd = (RequestCMD)cmd;
  fscanf(stdin, "%d", &request.param_num);
  for (i = 0; i < request.param_num; i++) {
    request.params[i] = ptr;
    fscanf(stdin, "%s", ptr);
    ptr = ptr + strlen(ptr) + 1;
  }
  return &request;
}

int * send_response() {
  int i;
  fprintf(stdout, "%d %d ", response.rs, response.param_num);
  for (i = 0; i < response.param_num; i++) {
    fputs(response.params[i],stdout);
    fputs(" ", stdout);
  }
  fflush(stdout);
  return 0;
}

//client side function

int * send_request() {
  int i;
  fprintf(stdout, "%d %d ", request.cmd, request.param_num);
  for (i = 0; i < request.param_num; i++) {
    fputs(request.params[i],stdout);
    fputs(" ", stdout);
  }
  fflush(stdout);
  return 0;
}


Response * get_response() {
  char * ptr = buf;
  int i; 
  int rs;
  memset(buf, 0, sizeof(buf));
  fscanf(stdin, "%d", &rs); 
  response.rs= (ResponseStatus)rs;
  fscanf(stdin, "%d", &response.param_num);
  for (i = 0; i < response.param_num; i++) {
    response.params[i] = ptr;
    fscanf(stdin, "%s", ptr);
    ptr = ptr + strlen(ptr) + 1;
  }
  return &response;
}

