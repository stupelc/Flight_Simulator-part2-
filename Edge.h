//
// Created by almogg on 1/13/19.
//

#ifndef PROJECT2_EDGE_H
#define PROJECT2_EDGE_H

#include "State.h"

class Edge{
    State<int>* src;
    State<int>* dest;
public:
    Edge(State<int> *src, State<int> *dest) : src(src), dest(dest) {}

    State<int>* getDest(){
        return this->dest;
    }

    State<int>* getSrc(){
        return this->src;
    }
};

#endif //PROJECT2_EDGE_H
