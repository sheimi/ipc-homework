IPC HOMEWORK
============

1. Overview
------------

    It is the homework of "Linux Programming" and is about IPC (Inter Process Comunication). 

    And this homework has to version:

    +   FIFO Version   (Stand-along)
    +   Socket Version (Network)

2. FIFO And Socket Interface
----------------------------

### 2.1 Interface

    Server Side: 
      int init_server();
      int wait_client(); 

    Client Side:
      init_client();
      close_client();
      
    (TODO)

### 2.2 FIFO

    (TODO)

### 2.3 SOCKET

    (TODO)

3. Server Design
----------------

### 3.1 Cocurent
    
    It is a Cocurent Server: Preforked Server, No Locking Around accept.

    (TODO)

4. Transaction Design
---------------------

### 4.1 The State Machie Model
------------------------------

                +----------------+
                |build Connection|-------------------------+
                +----------------+                         |
                        |                                  |
                        v                                  v
                +----------------+                     +-----------------+
        +-----> |  verify user   |-------------------->|distory connecton|
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

