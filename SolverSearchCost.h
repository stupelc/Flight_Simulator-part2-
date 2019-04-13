//
// Created by almogg on 1/9/19.
//

#ifndef PROJECT2_SOLVERSEARCHCOST_H
#define PROJECT2_SOLVERSEARCHCOST_H

#include "Solver.h"
#include "ISearcher.h"
#include <vector>

using std::vector;

//for the best search
//object adapter for connect solver to the searchable and searchar
template<class T>
class SolverSearchCost : public Solver<ISearcher<T>, int> {
protected:
    ISearchable<T> *iSearchable;
    ISearcher<T> *iSearcher;
    vector<ISearcher<T> *> allSearchers; // for all the searches available
public:
    //constructor for this solver
    //get the serachable
    SolverSearchCost(ISearchable<T> *iSearchable) {
        this->iSearchable = iSearchable;
    };

    //get the problem - the Iserceher - the alogritm - and return the solution
    //the total cost of this path
    int *solve(ISearcher<T> *p) override {
        //todo - search in the Isearchable with the ISeracher - the algoritm and return the total cost
    }
};

#endif //PROJECT2_SOLVERSEARCHCOST_H
