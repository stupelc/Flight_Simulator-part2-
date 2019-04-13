//
// Created by chagit on 1/15/19.
//

#include "MyParallelServer.h"
#define ZERO 0
#define ONE 1
#define TIME 5
//todo change the number - check what we need to change
#define TV_SEC 20
#define TV_USEC 0

void MyParallelServer::open(int port, ClientHandler *clientHandler) {
    int portno;
    int clilen, cliSock;
    struct sockaddr_in cli_addr;
    struct sockaddr_in serv_addr;

    // first call to socket() function
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    info->clientHandler = clientHandler;
    //initialize socket structure
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    // bind the host address using bind() call.
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }
    listen(sockfd, SOMAXCONN);
    clilen = sizeof(cli_addr);

    timeval timeout;
    timeout.tv_sec = TV_SEC;
    timeout.tv_usec = TV_USEC;

    //start listening to the client
    while (true) {
        cliSock = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
        info->sockfd = cliSock;
        if (cliSock < 0) {
            //end because of the timeout
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                stop();//close the trades
                break;//end the loop
            }
            perror("ERROR on accept");
            exit(1);
        }

        //setting timeout
        if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout)) == -1) {
            perror("ERROR on setting timeout");
        }

        pthread_t pthread;
        //create the tread to the client
        if (pthread_create(&pthread, nullptr, MyParallelServer::parallelService, info) != 0) {
            perror("thread failed");
        }
        this->threads.push_back(pthread);
    }
}

void MyParallelServer::stop() {
    for (auto thread: this->threads) {
        pthread_join(thread, nullptr);
    }
}

//initialize the params of the server
void* MyParallelServer::parallelService(void* newParams) {
    struct params *info = (struct params*)newParams;
    int sockfd = info->sockfd;
    info->clientHandler->handleClient(sockfd);
}
