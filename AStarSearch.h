//
// Created by almogg on 1/15/19.
//

#ifndef PROJECT2_ASTARSEARCH_H
#define PROJECT2_ASTARSEARCH_H


#include "Searcher.h"
#include <queue>
#include <iostream>

//algoritm of searcher
template<class T>
class AStarSearch : public Searcher<T> {
public:
    struct CompareStateCost {
        //for compare the cost of the sates so the priority queue could sort by it
        bool operator()(const State<T> *stateFirst, const State<T> *stateSecond) {
            //compare the f function - g + huristic of the state
            double fFirst = stateFirst->getHeuri() + stateFirst->getTrailcost();
            double fSecond = stateSecond->getHeuri() + stateSecond->getTrailcost();

            return (fFirst > fSecond);
            //return (stateFirst->getCost() > stateSecond->getCost());
        }
    };

    //constructor
    AStarSearch() {
        Searcher<T>::nodesNumer = 0;
    }

    //calculate "Manhattan" distance - the "pitagorace" of the distance
    double heuristic(State<T> *state, State<T> *goal) {

    }

    //we want to search by this searcher  in the searchable
    string search(ISearchable<T> *Isearchable) {
        Searcher<T>::nodesNumer=0;

        //cost of a specific node from the start
        int costNodeFromStart = 0;
        int pathCost = 0;
        double estimated = 0;
        // priority_queue<State<T> *> open; //priority queue
        vector<State<T> *> closedVect;
        vector<State<T> *> openVect;

        priority_queue<State<T> *, vector<State<T> *>, CompareStateCost> openPriQ; //using the compareator of priority queue

        State<T> *state = Isearchable->getInitializeState(); //take the first - the init state
        state->setHeuri(0); //dont have huri - it 0

        typename vector<State<T> *>::iterator it;
        bool isFound = false;

        //like the g function
        state->setTrailcost(state->getCost()); //change to the cost of it

        openPriQ.push(state); //put the first in the queue

        //as long as the queue not empty and didnt found the goal state
        while ((openPriQ.empty() == false) && (isFound == false)) {
            Searcher<T>::nodesNumer++;

            //take the first - the one in the front - the minimum
            state = openPriQ.top(); //the first - priority by f function
            openPriQ.pop(); //take it out
            closedVect.push_back(state);//put it in the close vector

            std::cout << state->getState() << std::endl;

            //check if it is the goal state
            if (state == Isearchable->getGoalState()) {
                //change the boolian of the found
                isFound = true;
            } else {

                //check if not in the close vector
                //run on all the negibors and add them
                vector<State<T> *> neighbors = Isearchable->getAllPossibleStates(state);

                typename vector<State<T> *>::iterator it;
                //run on all the negibhors
                for (it = neighbors.begin(); it != neighbors.end(); it++) {
                    estimated = state->getTrailcost() + (*it)->getCost(); //the tentative 'g' function

                    //g - is the trail cost
                    //check if its in the close vector or if the estimated is bigger or equal
                    if ((find(openVect.begin(), openVect.end(), *it) != openVect.end()) ||
                        estimated >= (*it)->getTrailcost()) {
                        continue;
                    }

                    //check if not in the open or g estimated is smaller thrn it know
                    if ((find(openVect.begin(), openVect.end(), *it) == openVect.end()) ||
                        estimated < (*it)->getTrailcost()) {
                        //changed the from to this state to be its parent
                        (*it)->setFrom(state);
                        (*it)->setTrailcost(estimated);//change the "g" - trail cost
                        double hur = Isearchable->getHuristic(*it,
                                                              Isearchable->getGoalState()); //get the distance - the huristic
                        (*it)->setHeuri(hur); //change the huristic - the "h"
                        //add it to the open priority queue - if not there
                        if (find(openVect.begin(), openVect.end(), *it) == openVect.end()) {
                            //add to open vector and queue
                            openPriQ.push(*it);
                            openVect.push_back(*it);
                        }
                    }

                }
            }
        }
      //  std::cout << "TRAIL COST " << Isearchable->getGoalState()->getTrailcost() << std::endl;
     //   std::cout << "V Number " << Searcher<T>::nodesNumer << std::endl;

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


#endif //PROJECT2_ASTARSEARCH_H
