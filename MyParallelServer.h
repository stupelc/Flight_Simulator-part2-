//
// Created by chagit on 1/15/19.
//

#ifndef PROJECT2_MYPARALLELSERVER_H
#define PROJECT2_MYPARALLELSERVER_H

#include "Server.h"
#include <vector>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>

using namespace server_side;

//responsible to open some clients at the same time
class MyParallelServer:public Server{
private:
    //vector of all the treads that we are going to open
    vector<pthread_t> threads;
    //vector for closing all the threads (the thread and his socketId)
    vector<pair<pthread_t,int>> closeServer;
    //struct for saving every clientHandler diverged (his specific socketId)
    struct params {
        ClientHandler* clientHandler;
        int sockfd;
    };
    //struct from thte type params
    struct params *info = new params();


public:
    //open the server in the port and wait for the customer - connection
    void open(int port, ClientHandler *clientHandler) override;

    //close the server
    void stop() override;

    //initialize the params of the server
    static void* parallelService (void* params);

    //destructor
    ~MyParallelServer(){
        delete info;
    }
};


#endif //PROJECT2_MYPARALLELSERVER_H
