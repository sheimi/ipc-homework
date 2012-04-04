IPC HOMEWORK
============

What's New
----------

+   Socket Version Server(fork and process pool)

Overview
------------

It is the homework of "Linux Programming" and is about IPC (Inter Process Communication). 

And this homework has two versions:

+   FIFO Version   (Stand-along)
+   Socket Version (Network)

Make
----

### 0. Before Make

Before make it, sqlite3 should be installed
    
### 1. Make Overview
    
    make [SERVER=[fork/pool(default: pool)](socket only)] [TYPE=[fifo/socket](default: socket)] [DEBUG=1] [SQLITE={the path of sqlite (default: /usr/lib/sqlite3)}]

### 2. To Make a FIFO Version

    make TYPE=fifo

### 3. To Make a Socket Version with process pool

    make

### 4. To Make a Socket Version with normal fork 

    make SERVER=fork

### 5. To Make a Debug Version

    make DEBUG=1

Run
---

The SQL File is ./db/train.sql
DB File is ./db/train.db
log File is ./db/ticket.log

    client

    server [num (the number of preforked process)]

    log file : data/ticket.log


FIFO And Socket Interface
----------------------------

    Server Side: 
      /*
       *  to init the server, including:
       *    open the public fifo or socket
       */
      int init_server();
      
      /*
       *  waiting for the connect from the server, including:
       *    wait for the connection
       *    dup the fifo or socket descriptors to two files 
       *
       */
      int wait_client(); 

    Client Side:
      /*
       *  to init the fifo for socket client, including:
       *    try to connect to the server
       *    dup the descriptors to two files
       *
       */
      init_client();
      /*
       *  to close the client, including:
       *    try to close to descriptors
       */
      close_client();
      
Server Design
----------------

### 1. Concurrent
    
It is a Cocurent Server: Preforked Server, No Locking Around accept.
    
        +----------+                                +---------+
        | client 1 |<------------------------------>| child 1 |<-----------fork--------\
        +----------+                                +---------+                         \
                                                                                         \
                                                                                          \
        +----------+                                +---------+                            +-----------+
        | client 2 |<------------------------------>| child 2 |<-----------fork------------|   parent  |
        +----------+                                +---------+                           /+-----------+
                                                                                         /      ^
                                                    +---------+                         /       |
                                                    | child 3 |<-----------fork--------/        |
                                                    +---------+                                 |
                                                                                                |
                                                      ......                                    |
                                                                                                |
                                                    +---------+                                 |
                                                    | child 4 |<-----------fork-----------------|
                                                    +---------+



#### 1.1 FIFO

Use a file lock to let the multiprocess "listen" to a file (read block)

#### 1.2 SOCKET

Linux and BSD(4.4+) allow multiprocess accept a socket, so it doesn't
need a file lock


Protocal Design
---------------

### 1. Overview

The Protocal are implemented by Request and Response.
Use string to communication and separated by blank

### 2. Request

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


### 3. Response

    typedef enum _request_status {
      SUCCESS,
      FAILED,
    } ResponseStatus;

    typedef struct _response {
      ResponseStatus rs;                // Response status from the server
      int length;                       // The length of response data
      char * data;                      // the reponse data
    } Response;


Transaction Design
---------------------

### 1. The State Machie Model

                +----------------+
                |build Connection|-------------------------+
                +----------------+                         |
                        |                                  |
                        v                                  v
                +----------------+                     +-----------------+
        +-----> |  verify user   |-------------------->| close connecton |
        |       +----------------+                     +-----------------+
        |failed    |    |                                  ^  ^
        +----------+    |success                           |  |
                        v                                  |  |
                +---------------+                          |  |
        +------>|  user request |--------------------------+  |
        |       +---------------+                             |
        |               |                                     |
        |continue       v                                     |
        |       +---------------+                             |
        +------>| return result |-----------------------------+
                +---------------+



What's More
-----------

### 1. What Have Been Implemented

+   fifo server
+   fifo lock
+   socket server
+   normal fork socket server
+   concurrent server
+   a simple process pool

+   login
+   register
+   order a ticket
+   query 
+   refund
+   sell log (without lock)

### 2. ToDo List (Next Version)

+   log lock
+   some other concurrent server model (select, asynchronize io(epoll) .... ) 

### 3. What Will Not Be Considered 

+   user interface (GUI or TUI)
+   more complex transaction 
