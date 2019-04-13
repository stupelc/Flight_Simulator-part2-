//
// Created by almogg on 1/3/19.
//

#ifndef PROJECT2_SERVER_H
#define PROJECT2_SERVER_H

#include "ClientHandler.h"

namespace server_side {
    class Server {
    protected:
        bool shouldStop = false;
    public:
        //todo - make sure not needded virtual
        //open the server in the port and wait for the customer - connection
        virtual void open(int port, ClientHandler *clientHandler) = 0;

        //close the server
        virtual void stop() = 0;
    };
}

#endif //PROJECT2_SERVER_H
