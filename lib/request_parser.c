#include <lib/request_parser.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
  fpurge(readport);
  return &request;
}

int send_response(ResponseStatus rs, int length, char * data) {
  fprintf(writeport, "%d %d ", rs, length);
  fwrite(data, sizeof(char), length, writeport);
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
  int rs;

  if (response.length > 0) {
    free(response.data);
  }

  fscanf(readport, "%d", &rs); 
  response.rs= (ResponseStatus)rs;
  fscanf(readport, "%d", &(response.length));


  if (response.length > 0) {
    response.data = (char *)(malloc(sizeof(char) * response.length));
    fread(response.data, sizeof(char), response.length, readport);
  }
  fpurge(readport);
  return &response;
}

