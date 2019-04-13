//
// Created by almogg on 1/9/19.
//

#ifndef PROJECT2_SEARCHER_H
#define PROJECT2_SEARCHER_H

#include "ISearcher.h"
#include <queue>

using std::priority_queue;

//the Abstract class for Isearcher
template<class T>
class Searcher : public ISearcher<T> {
protected:
    priority_queue<State<T> *> myQueue;
public:
    //constructor of a new Searcher
    Searcher() {
        // this->myQueue = new priority_queue<T>;

    }

    //todo - the 0 can be change - need to check - if need something else to be duplicate
    //method for the search function - search in the searchable
    //update the number of nodes and return string of the path
    //in the end - update with this node cost
    virtual string search(ISearchable<T> *Isearchable) = 0;

    //return the ost of al the nodes - member
    virtual int getCostOfNodes() {
        return this->costOfAllNodes;
    }

    virtual //return the next state in the queue
    State<T> *popList() {
//        this->nodesNumer++; //plus one to the nodes we been
//        //check not empty
//        if (this->myQueue.empty() == false) {
//            return this->myQueue.pop();
//        }
    };

};

#endif //PROJECT2_SEARCHER_H
