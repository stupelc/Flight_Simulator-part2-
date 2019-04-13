//
// Created by almogg on 1/3/19.
//

#ifndef PROJECT2_SOLVER_H
#define PROJECT2_SOLVER_H

template<class Problem, class Solution>
class Solver {
public:
    Solver(){

    };
    //Solver(Problem prob, Solution sol);
    virtual Solution solve(Problem p){};
};

#endif //PROJECT2_SOLVER_H
