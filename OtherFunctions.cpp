//
// Created by almogg on 1/7/19.
//

#include <memory.h>
#include "OtherFunctions.h"

//todo understand
vector<string> split(string line, string delimiter) {
    vector<string> data;
    size_t pos = 0;
    while ((pos = line.find(delimiter)) != string::npos) {
        if (!line.substr(0, pos).empty()) {
            data.push_back(line.substr(0, pos));
        }
        line.erase(0, pos + delimiter.length());
    }
    data.push_back(line.substr(0, pos));
    return data;
}