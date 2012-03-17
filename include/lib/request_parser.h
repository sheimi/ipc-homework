#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

#include <stdio.h>

#define MAX_PARAM_NUM 10

typedef enum _request_cmd {
  LOGIN,  
  REGISTER,
  QUIT,
  QUERY_STATIONS,
  QUERY_TRAIN,
  BUY_IT,
  QUERY_ORDERS,
  REFUND,
} RequestCMD;

typedef struct _request {
  RequestCMD cmd;                   // The cmd type send from client
  int param_num;                    // The the number of parameters 
  char * params[MAX_PARAM_NUM];     // The parameters
} Request;

typedef enum _request_status {
  SUCCESS,
  FAILED,
} ResponseStatus;

typedef struct _response {
  ResponseStatus rs;                // Response status from the server
  int length;                       // The length of response data
  char * data;                      // the reponse data
} Response;


//server side function

Request  * get_request();
int send_response(ResponseStatus rs, int length, char * data); 

//client side function

int send_request(RequestCMD cmd, int num, char * params[]); 
Response * get_response();

extern FILE * readport;
extern FILE * writeport;
#endif
