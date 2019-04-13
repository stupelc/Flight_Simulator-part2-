//
// Created by almogg on 1/14/19.
//

#ifndef PROJECT2_MATRIXFILECACHEMANAGER_H
#define PROJECT2_MATRIXFILECACHEMANAGER_H

#include "CacheManager.h"
#include "OtherFunctions.h"
#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Matrix.h"

#define DEVIDE_SIGH "$"

using namespace std;

//template<class P, class S>
//cache manager of files
class MatrixFileCacheManager : public CacheManager<Matrix *, string> {
    //map between problem and solution - matrix and the way to go out of it
    map<Matrix *, string> cache;
    string path;
    vector<Matrix *> toDelete;

public:
    //constructor of a new file cache manager
    //get a path of the file
    //put in the map all the cache from the file
    MatrixFileCacheManager(string path) {
        this->path = path;
        //for the problem - diverged with '$'
        //for the solution - diverged with '$$'

        ifstream readFile;
        readFile.open(path);
        if (readFile.is_open()) {
            //__throw_bad_exception();

            //}
            //the lines of the matrix
            vector<string> lines;
            string solution;
            string line;
            bool inNewMtrix = true, inSolution = false;
            while (getline(readFile, line)) {
                if (line == "$") {
                    inSolution = true;
                    inNewMtrix = false;
                }
                if (line == "$$") {
                    inNewMtrix = true;
                    inSolution = false;
                    //create the matrix from the lines
                    Matrix *mat = new Matrix(lines);
                    this->toDelete.push_back(mat);

                    this->cache.insert(pair<Matrix *, string>(mat, solution));
                    lines.clear();
                }
                if (inNewMtrix) {
                    lines.push_back(line);
                }
                if (inSolution) {
                    solution = line;
                }
            }
            readFile.close();
        }
    };

    bool isSolutionExist(Matrix *prob) override {
        //check the map
        typename ::map<Matrix *, string>::iterator it = this->cache.find(prob);

        //if its not the end - have the solution
        if (it != this->cache.end()) {
            return true; //the solution exist
        } else {
            return false; // solution not exist
        }

    };

    string getSolution(Matrix *prob) override {
        typename ::map<Matrix *, string>::iterator it = this->cache.find(prob);

        //if its not the end - have the solution
        if (it != this->cache.end()) {
            return (*it).second; // the solution from the table
        }
    };

    //save all the problems with solution that wasnt in the file
    bool saveSolution(Matrix *prob, string sol) override {
        //the problem
        vector<string> lines = prob->getAllLines();

        ofstream ofs;
        ofs.open(this->path, ios::out | ios::app | ios::ate);
        if (ofs.is_open()) {

            for (auto line:lines) {
                ofs << line << "\n";
            }
            ofs << "$" << "\n";
            ofs << sol << "\n";
            ofs << "$$" << "\n";

            ofs.close();
        }
    }
};


#endif //PROJECT2_MATRIXFILECACHEMANAGER_H
