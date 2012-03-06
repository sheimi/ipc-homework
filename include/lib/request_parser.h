#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

typedef enum _request_cmd {
  LOGIN,  
  REGISTER,
  QUIT,
} RequestCMD;

typedef struct _request {
  RequestCMD cmd;
  int param_num;
  char * params[];
} Request;

typedef enum _request_status {
  LOGIN_R,
  REGISTER_R,
} ResponseStatus;

typedef struct _response {
  ResponseStatus rs;
  int param_num;
  char * params[];
} Response;


//server side function

Request  * get_request();
int * send_response();

//client side function

int * send_request();
Response * get_response();

extern Request request;
extern Response response;

#endif
