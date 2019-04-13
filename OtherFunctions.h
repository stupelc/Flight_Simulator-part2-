//
// Created by almogg on 1/7/19.
//

#ifndef PROJECT2_OTHERFUNCTIONS_H
#define PROJECT2_OTHERFUNCTIONS_H

//for all other functions

#include <string>
#include <vector>
#include <sstream>
#include <istream>

#define BUFF_SIZE 256

using namespace std;

//get a template object and return its string value
//template<class T>
//string tempToString(T temp) {
//    ostringstream myObjectStream; // a stream is built
//    myObjectStream << temp; // the stream is filled
//
//    string mySerializedObject = myObjectStream.str();
//
//    return mySerializedObject;
//}


//split the line according to a given delimiter
vector<string> split(string line, string delimiter);



#endif //PROJECT2_OTHERFUNCTIONS_H
