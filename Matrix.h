//
// Created by almogg on 1/9/19.
//

#ifndef PROJECT2_MATRIX_H
#define PROJECT2_MATRIX_H

#include "Searchable.h"
#include "Point.h"
#include "OtherFunctions.h"
#include <vector>

using std::vector;

class Matrix : public Searchable<Point> {
    //contains all the lines of the matrix
    vector<string> allLines;
    //colSize and rowSize of the matrix
    int colSize;
    int rowSize;

    //lists
    vector<State<Point> *> listStates;

public:
    Matrix();

    //the constructor of the matrix
    Matrix(vector<State<Point> *> structure, State<Point> *initialState, State<Point> *goal, vector<string> lines) {
        this->goalState = goal;
        this->initialState = initialState;
        this->structure = structure;
        this->allLines = lines;
    }

    //upside down matrix - get all the lines according to what we gor in the buffer and creates new matrix
    Matrix(vector<string> lines) {
        //update the values that we got
        this->allLines=lines;
        this->rowSize = allLines.size() - 2;
        this->colSize = split(allLines[0], ",").size();

        vector<string> temp;
        temp = split(allLines[allLines.size() - 2], ",");
        //check if got 2 values in it
        if (temp.size() == 2) {
            this->initialState = new State<Point>(Point(stoi(temp[0]), stoi(temp[1])), 0);
            listStates.push_back(initialState);
        }

        //update the initialize state
        temp = split(allLines[allLines.size() - 1], ",");
        //check if got 2 values in it
        if (temp.size() == 2) {
            this->goalState = new State<Point>(Point(stoi(temp[0]), stoi(temp[1])), 0);
            listStates.push_back(goalState);
        }

        //update the matrix values
        for (int i = 0; i < rowSize; i++) {
            temp = split(allLines[i], ",");
            for (int j = 0; j < colSize; ++j) {
                if (initialState->getState().getX() == i && initialState->getState().getY() == j) {
                    this->initialState->setCost(stod(temp[j]));
                    this->structure.push_back(initialState);
                } else if (goalState->getState().getX() == i && goalState->getState().getY() == j) {
                    this->goalState->setCost(stod(temp[j]));
                    this->structure.push_back(goalState);
                } else {
                    State<Point> *state = new State<Point>(Point(i, j), stod(temp[j]));
                    this->structure.push_back(state);
                    this->listStates.push_back(state);
                }
            }
        }
    }

    //get the possible moves in a current state of the matrix
    vector<State<Point> *> getAllPossibleStates(State<Point> *currentState) override;

    string getRoute() override;

    double getHuristic(State<Point> *start, State<Point> *goal) override;

    const vector<string> &getAllLines() const;

    void setAllLines(const vector<string> &allLines);

    int getColSize() const;

    void setColSize(int colSize);

    int getRowSize() const;

    void setRowSize(int rowSize);

    virtual ~Matrix();
};

#endif //PROJECT2_MATRIX_H