//
// Created by almogg on 1/7/19.
//

#include "StringReverser.h"

//StringReverser::StringReverser() {

//}

string StringReverser::solve(string p) {
    //need to revers the string
    int i = 0;
    string reverse = "";
    //run on every char in the string and put from end to start
    for (i = p.length() - 1; i >= 0; i--) {
        //take from here and put in the revrs string
        reverse += p.at(i);
    }
    //return the new string
    return reverse;
}
