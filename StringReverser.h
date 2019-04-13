//
// Created by almogg on 1/7/19.
//

#ifndef PROJECT2_STRINGREVERSER_H
#define PROJECT2_STRINGREVERSER_H

#include "Solver.h"
#include <string>

using std::string;

//template <class P,class S>
class StringReverser : public Solver<string, string> {
public:
    StringReverser() {

    };

    string solve(string p);

};

#endif //PROJECT2_STRINGREVERSER_H
