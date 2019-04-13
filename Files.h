//
// Created by almogg on 1/7/19.
//

#ifndef PROJECT2_FILES_H
#define PROJECT2_FILES_H

#include <string>

using namespace std;

//for all things with files - all methods need to do things with the file

class File {
    //have file name
    string fileName;
public:
    File(string name);

    //read information from file to map
    void readFromFile();
    //write to the file the information
};

#endif //PROJECT2_FILES_H
