//
// Created by almogg on 1/9/19.
//

#ifndef PROJECT2_BESTFIRSTSEARCH_H
#define PROJECT2_BESTFIRSTSEARCH_H

#include "Searcher.h"
#include <queue>
#include <iostream>

using std::cout;
using std::endl;

//algoritm of searcher
template<class T>
class BestFirstSearch : public Searcher<T> {
public:
    struct CompareStateCost {
        //for compare the cost of the sates so the priority queue could sort by it
        bool operator()(const State<T> *stateFirst, const State<T> *stateSecond) {
            // bool is = stateFirst < stateSecond;
            return (stateFirst->getCost() > stateSecond->getCost());
        }
    };

    BestFirstSearch() {
        Searcher<T>::nodesNumer = 0;
    }

    //we want to search by this searcher  in the searchable
    string search(ISearchable<T> *Isearchable) {
        Searcher<T>::nodesNumer = 0;

        //cost of a specific node from the start
        int costNodeFromStart = 0;

        // priority_queue<State<T> *> open; //priority queue
        vector<State<T> *> closedVect;
        vector<State<T> *> openVect;

        priority_queue<State<T> *, vector<State<T> *>, CompareStateCost> openPriQ; //using the compareator of priority queue

        State<T> *state = Isearchable->getInitializeState(); //take the first - the init state
        state->setTrailcost(state->getCost());

        typename vector<State<T> *>::iterator it;
        bool isFound = false;

        openPriQ.push(state); //put the first in the queue

        //as long as the queue not empty and didnt found the goal state
        while ((openPriQ.empty() == false) && (isFound == false)) {

            Searcher<T>::nodesNumer++;

            //take the first - the one in the front - the minimum
            state = openPriQ.top(); //the first
            openPriQ.pop(); //take it out

            std::cout << state->getState() << std::endl;

            //check if it is the goal state
            if (state == Isearchable->getGoalState()) {
                //change the boolian of the found
                isFound = true;
            } else {

                //check if not in the close vector
                if (find(closedVect.begin(), closedVect.end(), state) == closedVect.end()) {
                    //run on all the negibors and add them
                    vector<State<T> *> statesToOpen = Isearchable->getAllPossibleStates(state);

                    typename vector<State<T> *>::iterator it;
                    //run on all the negibhors
                    for (it = statesToOpen.begin(); it != statesToOpen.end(); it++) {
                        //just if not in close list
                        if (find(openVect.begin(), openVect.end(), *it) == openVect.end()) {
                            //changed the from
                            (*it)->setFrom(state);
                            (*it)->setTrailcost((*it)->getCost() + state->getTrailcost());

                            //take the state and do it in this state
                            openPriQ.push(*it);//push the neigbhor to the queue
                            openVect.push_back(*it); //for not be duplicate
                        }
                    }
                    //put the state in the closed vector - the visited
                    closedVect.push_back(state);
                    openVect.push_back(state);
                }
            }
        }
        //  std::cout << "TRAIL COST " << Isearchable->getGoalState()->getTrailcost() << std::endl;
        //std::cout << "V Number " << Searcher<T>::nodesNumer << std::endl;

      //  std::cout << Isearchable->getGoalState()->getTrailcost() << "," << Searcher<T>::nodesNumer << std::endl;

        return Isearchable->getRoute();

    }


//    int numberOFNodes() override {
//        return ISearcher::numberOFNodes();
//    }
//
//    BestFirstSearch() : Searcher() {
//
//    }
//
//    int getCostOfNodes() override {
//        return Searcher::getCostOfNodes();
//    }
//
//    State<T> *popList() override {
//        return Searcher::popList();
//    }
};

#endif //PROJECT2_BESTFIRSTSEARCH_H
