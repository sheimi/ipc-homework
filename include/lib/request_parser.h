#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

#include <stdio.h>

#define MAX_PARAM_NUM 10

typedef enum _request_cmd {
  LOGIN,  
  REGISTER,
  QUIT,
} RequestCMD;

typedef struct _request {
  RequestCMD cmd;
  int param_num;
  char * params[MAX_PARAM_NUM];
} Request;

typedef enum _request_status {
  SUCCESS,
  FAILED,
} ResponseStatus;

typedef struct _response {
  ResponseStatus rs;
  int param_num;
  char * params[MAX_PARAM_NUM];
} Response;


//server side function

Request  * get_request();
int send_response(ResponseStatus rs, int num, char * params[]); 

//client side function

int send_request(RequestCMD cmd, int num, char * params[]); 
Response * get_response();

extern FILE * readport;
extern FILE * writeport;
#endif
