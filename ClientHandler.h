//
// Created by almogg on 1/3/19.
//

#ifndef PROJECT2_CLIENTHANDLER_H
#define PROJECT2_CLIENTHANDLER_H

#include <iostream>

using namespace std;

class ClientHandler {
public:
    //get socket id to open it,read and write things to him
    virtual void handleClient(int socketId) = 0;
};

#endif //PROJECT2_CLIENTHANDLER_H
