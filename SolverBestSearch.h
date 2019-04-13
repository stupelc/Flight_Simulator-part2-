//
// Created by almogg on 1/9/19.
//

#ifndef PROJECT2_SOLVERBESTSEARCH_H
#define PROJECT2_SOLVERBESTSEARCH_H

#include "Solver.h"
#include "ISearcher.h"
#include <vector>

using std::vector;

//object adapter for connect solver to the searchable and searchar
//get a searchable and list of all searchers - and return a new Isearcher
//of the fastest alogritm - the less cost
template<class T>
class SolverBestSearch : public Solver<ISearchable<T>*, string> {
protected:
    ISearchable<T> *iSearchable;
    ISearcher<T> *iSearcher;
    vector<ISearcher<T> *> allSearchers; // for all the searches available
public:
    //constructor for this solver
    //the consturcor is get all possible agloritms of serchers
    SolverBestSearch(vector<ISearcher<T> *> searches) {
        this->allSearchers = searches;
    };

    SolverBestSearch(ISearcher<T> *iSearcher) : iSearcher(iSearcher) {}

    SolverBestSearch() {}

    //get the problem - the Isearcble - and return the solution
    //the solution is the best search path
    string solve(ISearchable<T>* p) override {
        return this->iSearcher->search(p);
        //todo need to run on all the searchers and compare  between the cost of each

        //minimum - the best - save
        //todo to print to file the cost of each
    }


};

#endif //PROJECT2_SOLVERBESTSEARCH_H
