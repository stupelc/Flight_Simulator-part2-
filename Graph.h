//
// Created by almogg on 1/10/19.
//

#ifndef PROJECT2_GRAPH_H
#define PROJECT2_GRAPH_H

#include "Edge.h"
#include "Searchable.h"
#include <list>
#include <map>

using std::list;
using std::vector;
using std::map;

//represent a graph
//template<class T>
class Graph : public Searchable<int> {

    int V;    // No. of vertices
    State<int>* initSt;
    State<int>* goalSt;

    // Pointer to an array containing
    // adjacency lists

    vector<Edge*> edges;
public:
    vector<State<int> *> getAllPossibleStates(State<int> *currentState) {
        vector<State<int>*> possible;
        //take from the list of edges
        std::vector<Edge*>::iterator it;
        for(it = this->edges.begin(); it != this->edges.end(); it++){
            //get dest
            //take all the currentStates
           if((*it)->getSrc() == currentState){
               possible.push_back((*it)->getDest()); //add the dest
           }
        }
        return possible;
      //  return this->adj[currentState->getState()];
        //return this->adj; //return the vector of all adjecency states
    };

    State<int> *getInitializeState() override {
        return this->initSt;
    }

    State<int> *getGoalState() override {
        return this->goalSt;
    }

    void setStructure(vector<State<int> *> structure) override {
       // Searchable::setStructure(structure);
    }

    void setInitialState(State<int> *initialState) override {
        //Searchable::setInitialState(initialState);
    }

    void setGoalState(State<int> *goalState) override {
    }

//    string getRoute() override {
//        return Searchable::getRoute();
//    }

    Graph(int V,State<int>* init,State<int>* goal) {
        this->V = V;
        this->initSt = init;
        this->goalSt = goal;
    };   // Constructor

    // function to add an edge to graph
    void addEdge(State<int> *v, State<int> *w) {
        this->edges.push_back(new Edge(v,w));
    };

};
#endif //PROJECT2_GRAPH_H
