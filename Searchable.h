//
// Created by almogg on 1/9/19.
//

#ifndef PROJECT2_SEARCHABLE_H
#define PROJECT2_SEARCHABLE_H

#include "ISearchable.h"
#include <algorithm>
#include <vector>
#include <string>

using std::vector;
using std::string;

template<class T>
class Searchable : public ISearchable<T> {
protected:
    std::vector<State<T> *> structure;
    State<T> *initialState;
    State<T> *goalState;

public:
    //for comparing states

    //return the initialize state of our 'problem'
    virtual State<T> *getInitializeState() {
        return this->initialState;
    }

    //return the goal state of our 'problem'
    virtual State<T> *getGoalState() {
        return this->goalState;
    }

    virtual vector<State<T> *> getStructure() {
        return this->structure;
    }

    //get the possible moves to the next step
    virtual vector<State<T> *> getAllPossibleStates(State<T> *currentState) = 0;

    //apply the structure that we got from the user - our problem
    void setStructure(vector<State<T> *> structure) {
        this->structure = structure;
    }

    //set the initial state of the searchable item
    void setInitialState(State<T> *initialState) {
        this->initialState = initialState;
    }

    //set the goal state of the searchable item
    void setGoalState(State<T> *goalState) {
        this->goalState = goalState;
    }

    //get the string of our way to the end
    string getRoute() override = 0;

    virtual double getHuristic(State<T> *start, State<T> *goal) override {
       // return ISearchable::getHuristic(start, goal);
    }


};


#endif //PROJECT2_SEARCHABLE_H
