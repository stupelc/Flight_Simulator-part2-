//
// Created by almogg on 1/3/19.
//

#ifndef PROJECT2_FILECACHEMANAGER_H
#define PROJECT2_FILECACHEMANAGER_H

#include "CacheManager.h"
#include "OtherFunctions.h"
#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Matrix.h"

#define DEVIDE_SUL_TO_PRO "$$"
#define DEVIDE_PRO_TO_SUL "$"


using namespace std;
static pthread_mutex_t mutex;


//cache manager of files
class FileCacheManager : public CacheManager<Matrix *, string> {
    //map between problem and solution - matrix and the way to go out of it
    //map<Matrix *, string> cache;
    map<vector<string>, string> cache;

    string path;
    vector<Matrix *> toDelete;

public:
    //constructor of a new file cache manager
    //get a path of the file
    //put in the map all the cache from the file
    FileCacheManager(string path) {
        pthread_mutex_init(&mutex, nullptr);

        this->path = path;
        //for the problem - diverged with '$$'
        //for the solution - diverged with '$'
        pthread_mutex_lock(&mutex);

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
                if (line == DEVIDE_PRO_TO_SUL) {
                    inSolution = true;
                    inNewMtrix = false;
                }
                if (line == DEVIDE_SUL_TO_PRO) {
                    inNewMtrix = true;
                    inSolution = false;
                    //create the matrix from the lines
                    Matrix *mat = new Matrix(lines);
                    this->toDelete.push_back(mat);

                    this->cache.insert(pair<vector<string>, string>(mat->getAllLines(), solution));

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
        pthread_mutex_unlock(&mutex);
    };

    bool isSolutionExist(Matrix *prob) override {
        pthread_mutex_lock(&mutex);
        //check the map
        typename ::map<vector<string>, string>::iterator it = this->cache.find(prob->getAllLines());
        pthread_mutex_unlock(&mutex);

        //if its not the end - have the solution
        if (it != this->cache.end()) {

            return true; //the solution exist
        } else {
            return false; // solution not exist
        }

    };

    string getSolution(Matrix *prob) override {
        pthread_mutex_lock(&mutex);
        typename ::map<vector<string>, string>::iterator it = this->cache.find(prob->getAllLines());
        pthread_mutex_unlock(&mutex);

        //if its not the end - have the solution
        if (it != this->cache.end()) {
            return (*it).second; // the solution from the table
        }
    };

    //save all the problems with solution that wasnt in the file
    bool saveSolution(Matrix *prob, string sol) override {
        //the problem
        vector<string> lines = prob->getAllLines();
        pthread_mutex_lock(&mutex);
        this->cache.insert(pair<vector<string>, string>(prob->getAllLines(), sol));

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
        pthread_mutex_unlock(&mutex);

    }
};

#endif //PROJECT2_FILECACHEMANAGER_H
