#include <thread>
#include "MySerialServer.h"

#define ZERO 0
#define ONE 1
#define TIME 5

void MySerialServer::open(int port, ClientHandler *clientHandler){
    int sockfd, portno;
    struct sockaddr_in serv_addr;

    //call to socket() function
    sockfd = socket(AF_INET, SOCK_STREAM, ZERO);

    if (sockfd < ZERO) {
        perror("ERROR opening socket");
        exit(ONE);
    }

    //initialize socket structure
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    //now bind the host address using bind() call
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < ZERO) {
        perror("ERROR on binding");
        exit(1);
    }

    //tart listening for the clients, here process will
    //go in sleep mode and will wait for the incoming connection
    thread t(serialService, sockfd,clientHandler);
    t.detach();
}

void MySerialServer::serialService(int sockfd, ClientHandler* clientHandler) {
    int newsockfd, clilen;
    struct sockaddr_in cli_addr;

    //todo timeout


    while (true) {
        listen(sockfd, TIME);
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
        clientHandler->handleClient(newsockfd);
    }
}

//stop the connection after getting the message 'end'
void MySerialServer::stop() {

}