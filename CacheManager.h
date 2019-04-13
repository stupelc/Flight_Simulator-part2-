//
// Created by almogg on 1/3/19.
//

#ifndef PROJECT2_CACHEMANAGER_H
#define PROJECT2_CACHEMANAGER_H

//interface for caching the solutions
template<class P, class S>
class CacheManager {
public:
    CacheManager(){

    };
    //check if the solution exist in this cache
    virtual bool isSolutionExist(P prob){

    };

    //return the solution for this problem
    virtual S getSolution(P prob){

    };
    //todo check why cant virtual

    //save the specific solution in this cache
    //return true if success or false if not
    virtual bool saveSolution(P prob, S sol){

    };

};

#endif //PROJECT2_CACHEMANAGER_H
