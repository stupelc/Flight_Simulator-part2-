#ifndef PROJECT2_MYCLIENTHANDLER_H
#define PROJECT2_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include "FileCacheManager.h"
#include "OtherFunctions.h"
#include "Point.h"
#include "State.h"
#include "Matrix.h"
#include "ISearchable.h"
#include <vector>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <sstream>

#define BUFF_SIZE 256
#define ONE 1
#define ZERO 0

using namespace std;
//read from the client line after line and creates a matrix
//todo check if need generics because its a specific problem
template<class P, class S>
class MyClientHandler : public ClientHandler {
    //solver to solve this client
    Solver<P, S> *solver;
    //cache manager that the client will use
    //CacheManager<P, S> *cacheManager;
    FileCacheManager *cacheManager;
    //vector of elements to deleate at the end of the program
    vector<Matrix *> listSearchble;
    //vector of all the states to delete after that
    vector<State<Point> *> listStates;

public:
    MyClientHandler(Solver<P, S> *solver, FileCacheManager *cacheManager) : solver(solver),
                                                                            cacheManager(cacheManager) {}

    void handleClient(int socketId) override {
        //our charities for the matrix problem (searchable)
        State<Point> *initialState;
        State<Point> *goalState;
        vector<string> temp;
        vector<string> allLines;
        vector<State<Point> *> searchable;

        //our buffer that read the message
        char buffer[BUFF_SIZE];
        string line = "";
        string problem = "";
        string solution = "";
        ssize_t n;
        char *chr;

        //matrix charities
        int colSize, rowSize;
        bool endMatrix = false;

        //check if the id socket is correct
        if (socketId < ZERO) {
            perror("ERROR on accept");
            exit(1);
        }

        //the state line - according that we will know what information is in there
        //line no. 0 - col : the matrix
        //line no. col+1 - the initialize point state
        //line no. col+2 - the goal state
        //line no. col+3 - end
        int numMission = 0;
        //num to count the number of the rows
        int numLine = 0;

        string left = "";
        //if connection is established start to communicate
        while (true) {
            //clean the buffer - put 0 in all of him
            bzero(buffer, BUFF_SIZE);
            //read data from the buffer
            n = read(socketId, buffer, BUFF_SIZE - 1);

            //check if we get something in from the read function
            if (n < ZERO) {
                perror("ERROR reading from socket");
                exit(ONE);
            }

            //line += buffer; //add the line to the corrent buffer

            //read till the /n and returns the lines.s
            line = line + buffer;

            //without /n
            stringstream temp(line);
            //create from the line
            string segment;

            bool isWithSpace = false;

            //split by "/n"
            while (getline(temp, segment, '\n')) {
                isWithSpace = true;
                line = segment;
                if(!temp.eof() && segment != "end"){
                    allLines.push_back(line);
                }

            }
//            if (!isWithSpace) {
//                allLines.push_back(line);
//            }

            //if we got to the end of the problem

            if(line == "end" || line == "end\n"){
                break;
            }

            //if segment not empty - keep it
            if(segment == ""){
                line = "";
            }
            //read all lines from the client till got 'end'
           // allLines.push_back(line);

          //  line = "";
        }

//        //update the values that we got
//        rowSize = allLines.size() - 2;
//        colSize = split(allLines[0], ",").size();
//
//        //update the initialize state
//        temp = split(allLines[allLines.size() - 2], ",");
//        //check if got 2 values in it
//        if (temp.size() == 2) {
//            initialState = new State<Point>(Point(stoi(temp[0]), stoi(temp[1])), 0);
//            listStates.push_back(initialState);
//        }
//
//        //update the initialize state
//        temp = split(allLines[allLines.size() - 1], ",");
//        //check if got 2 values in it
//        if (temp.size() == 2) {
//            goalState = new State<Point>(Point(stoi(temp[0]), stoi(temp[1])), 0);
//            listStates.push_back(goalState);
//        }
//
//        //update the matrix values
//        for (int i = 0; i < rowSize; i++) {
//            temp = split(allLines[i], ",");
//            for (int j = 0; j < colSize; ++j) {
//                if (initialState->getState().getX() == i && initialState->getState().getY() == j) {
//                    initialState->setCost(stod(temp[j]));
//                    searchable.push_back(initialState);
//                } else if (goalState->getState().getX() == i && goalState->getState().getY() == j) {
//                    goalState->setCost(stod(temp[j]));
//                    searchable.push_back(goalState);
//                } else {
//                    State<Point> *state = new State<Point>(Point(i, j), stod(temp[j]));
//                    searchable.push_back(state);
//                    listStates.push_back(state);
//                }
//            }
//        }

        //create the matrix with all her variables
        //ISearchable<Point> *mat = new Matrix(allLines);
        Matrix *mat = new Matrix(allLines);
        this->listSearchble.push_back(mat);

        //check if there is a solution for the problem
        if (this->cacheManager->isSolutionExist(mat)) {
            solution = this->cacheManager->getSolution(mat);
        } else {
            solution = solver->solve(mat);
            cacheManager->saveSolution(mat, solution);
        }

        // write a response to the server
        chr = const_cast<char *>(solution.c_str());
        n = write(socketId, chr, strlen(chr));
        cout << solution << endl;

        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }
    }

    virtual ~MyClientHandler() {
        for (auto searchable:this->listSearchble) {
            delete searchable;
        }

        for (auto state:this->listStates) {
            delete state;
        }
    }

};

#endif //PROJECT2_MYCLIENTHANDLER_H