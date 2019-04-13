//
// Created by almogg on 1/9/19.
//

#ifndef PROJECT2_ISEARCHABLE_H
#define PROJECT2_ISEARCHABLE_H

#include "State.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

//interface for a thing to search in it
//the functional of the search problem
template<class T>
class ISearchable {
public:
    //get the initialize state - the source
    virtual State<T> *getInitializeState() = 0;

    //return the goal state - the detination state
    virtual State<T> *getGoalState() = 0;

    //return all the structure of the searchable
    virtual vector<State<T> *> getStructure() = 0;

    //return all the possible states - the structure in a vector
    virtual vector<State<T> *> getAllPossibleStates(State<T> *currentState) = 0;

    //update the searchable that we want
    virtual void setStructure(vector<State<T> *> structure) = 0;

    //set the initial state of the searchable item
    virtual void setInitialState(State<T> *initialState) = 0;

    //set the goal state of the searchable item
    virtual void setGoalState(State<T> *goalState) = 0;

    //get the huristic from start to goal
    virtual double getHuristic(State<T> * start,State<T>* goal){

    };

    virtual string getRoute() = 0;

    //todo - check if need pointer to vector
};

#endif //PROJECT2_ISEARCHABLE_H