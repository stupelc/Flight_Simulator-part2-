//
// Created by almogg on 1/3/19.
//

#ifndef PROJECT2_MYTESTCLIENTHANDLER_H
#define PROJECT2_MYTESTCLIENTHANDLER_H

#include <strings.h>
#include <unistd.h>
#include <cstring>
#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"

#define BUFF_SIZE 256
#define ONE 1
#define ZERO 0

template<class P, class S>
//read from the client line after line and between each line wait to response
class MyTestClientHandler : public ClientHandler {
    //solver to solve this client
    Solver<P, S> *solver;
    //cache manager that the client will use
    CacheManager<P, S> *cacheManager;
public:
    MyTestClientHandler(Solver<P, S> *solver, CacheManager<P, S> *cacheManager) : solver(solver),
                                                                                  cacheManager(cacheManager) {}

    void handleClient(int socketId) override {
        //our buffer that read the message
        char prob[BUFF_SIZE];
        string problem;
        string solution;
        ssize_t n;
        char *chr;

        //check if the id socket is correct
        if (socketId < ZERO) {
            perror("ERROR on accept");
            exit(1);
        }

        //if connection is established start to communicate
        while (true) {
            //clean the buffer - put 0 in all of him
            bzero(prob, BUFF_SIZE);
            //read data from the buffer
            n = read(socketId, prob, BUFF_SIZE - 1);
            //check if we get something in from the read function
            if (n < ZERO) {
                perror("ERROR reading from socket");
                exit(ONE);
            }
            //if we got to the end of the problem
            if ((strcmp(prob, "end")) == ZERO) {
                cout << prob << endl;
                exit(ZERO);
                return;
            }

            printf("Here is the message: %s\n", prob);

            //get solution from disk
            //if there are solution to the problem
            if (this->cacheManager->isSolutionExist(prob)) {
                solution = this->cacheManager->getSolution(prob);
            } else {
                solution = solver->solve(prob);
                cacheManager->saveSolution(prob,solution);
            }

            //write a response to the client
            chr = const_cast<char *>(solution.c_str());
            //write the solution to the socket
            n = write(socketId, chr, strlen(chr));
            cout << solution << endl;

            //check if the write successed
            if (n < ZERO) {
                perror("ERROR writing to socket");
                exit(ONE);
            }
        }
    }
};

#endif //PROJECT2_MYTESTCLIENTHANDLER_H
