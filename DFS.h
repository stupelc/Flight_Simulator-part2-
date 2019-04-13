//
// Created by almogg on 1/10/19.
//

#ifndef PROJECT2_DFS_H
#define PROJECT2_DFS_H

#include "Searcher.h"
#include <stack>
#include<iostream>
#include<list>
#include <deque>
#include <queue>
#include <map>

using std::stack;
using std::list;
using std::deque;
using std::queue;
using std::map;
using std::pair;

template<class T>
class DFS : public Searcher<T> {
    string path;
    vector<State<T> *> closedVector;
    stack<State<T> *> stackOpen;

    bool found;
public:
    DFS() {
        Searcher<T>::nodesNumer = 0;
        Searcher<T>::costOfAllNodes = 0;
    }

    int numberOFNodes() override {
        return Searcher<T>::numberOFNodes();
        //return ISearcher::numberOFNodes();
    }

    int getCostOfNodes() override {
        return Searcher<T>::getCostOfNodes();
    }

    State<T> *popList() override {
        //  return Searcher::popList();
    }

    //search in the searchable
    string search(ISearchable<T> *Isearchable) override {
        Searcher<T>::nodesNumer = 0;
        //take the init state from the searchable
        State<T> *state = Isearchable->getInitializeState();
        state->setTrailcost(state->getCost()); //set it trail cost

        State<T> *stateV;
        typename vector<State<T> *>::iterator it;

        bool visited = false;

        this->stackOpen.push(state); // put the init state in the stack
        this->found = false;

        typename map<State<T> *, bool>::iterator iter;

        //as long as the stack not empty
        while ((this->stackOpen.empty() == false) && (this->found == false)) {

            //take the first
            state = this->stackOpen.top();
            this->stackOpen.pop(); //take it out
            Searcher<T>::nodesNumer++;

            std::cout << state->getState() << std::endl;

            //check if it is the goal state
            if (state == Isearchable->getGoalState()) {
                //return the path
                this->found = true;
            } else {

                //check if not in the close vector
                if (find(this->closedVector.begin(), this->closedVector.end(), state) == this->closedVector.end()) {

                    //run on all the negibohors and add them
                    vector<State<T> *> statesToOpen = Isearchable->getAllPossibleStates(state);

                    typename vector<State<T> *>::iterator it;
                    for (it = statesToOpen.begin(); it != statesToOpen.end(); it++) {
                        //just if not in close list
                        if (find(this->closedVector.begin(), this->closedVector.end(), *it) ==
                            this->closedVector.end()) {
                            //changed the from
                            (*it)->setFrom(state);
                            (*it)->setTrailcost((*it)->getCost() + state->getTrailcost());

                            //take the state and do it in this state
                            this->stackOpen.push(*it); //push the negibor to the queue
                        }
                    }
                    this->closedVector.push_back(state);
                }
            }
        }
      //  std::cout<< "TRAIL COST "<<Isearchable->getGoalState()->getTrailcost()<<std::endl;
        //std::cout<< "V Number "<<Searcher<T>::nodesNumer <<std::endl;
        return Isearchable->getRoute();
    }


};

#endif //PROJECT2_DFS_H
