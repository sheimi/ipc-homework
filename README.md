IPC HOMEWORK
============

Overview
------------

    It is the homework of "Linux Programming" and is about IPC (Inter Process Comunication). 

    And this homework has to version:

    +   FIFO Version   (Stand-along)
    +   Socket Version (Network)

FIFO And Socket Interface
----------------------------

### 1. Interface

    Server Side: 
      int init_server();
      int wait_client(); 

    Client Side:
      init_client();
      close_client();
      
    (TODO)

### 2. FIFO

    (TODO)

### 3. SOCKET

    (TODO)

Server Design
----------------

### 1. Cocurent
    
    It is a Cocurent Server: Preforked Server, No Locking Around accept.

    (TODO)

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

    (TODO)

