//
// Created by almogg on 1/3/19.
//

#ifndef PROJECT2_MYSERIALSERVER_H
#define PROJECT2_MYSERIALSERVER_H

#include "ClientHandler.h"
#include "Server.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>

using namespace server_side;

class MySerialServer : public Server {
public:
    void open(int port, ClientHandler *clientHandler);

    void stop();

    static void serialService(int sockfd, ClientHandler *clientHandler);

};

#endif //PROJECT2_MYSERIALSERVER_H
