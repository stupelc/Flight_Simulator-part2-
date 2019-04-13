//
// Created by almogg on 1/8/19.
//

#ifndef PROJECT2_STATE_H
#define PROJECT2_STATE_H

#include <limits>

template<class T>
class State {
private:
    T myState;
    double cost;//current cost
    double trailcost; //how much cost to reach this state
    //int cost; //how much cost to reach this state
    State<T> *from;//the state we came from to this state
    double heuri; //for the huristic
public:
    //constructors
    State(T state) {
        this->myState = state;
        this->trailcost = std::numeric_limits<double>::infinity(); //init trail cost to infinity
    };

    State(T myState, double cost) : myState(myState),
                                    cost(cost) { this->trailcost = std::numeric_limits<double>::infinity(); }

    State(T myState, double trailcost, State<T> *from) : myState(myState), trailcost(trailcost),
                                                         from(from) { this->trailcost = std::numeric_limits<double>::infinity(); }

    //return the state T
    T getState() {
        return this->myState;
    };

    //change the from state
    void setFrom(State<T> *fromSt) {
        this->from = fromSt;
    };

    //return the from state of this state
    State<T> *getFrom() {
        return this->from;
    };

    //check if the states are equal
    bool equals(State<T> *state) {
        //compare
        if (this->myState == state->getState()) {
            return true;
        } else {
            return false;
        }
    };

    double getTrailcost() const {
        return trailcost;
    }

    void setTrailcost(double trailcost) {
        State::trailcost = trailcost;
    }

    int valueOfState() {
        //return the value of this state
        return this->cost;
    }

    //get the cost of the current state
    double getCost() const {
        return cost;
    }

    //initialize our cost for the current path
    void setCost(double cost) {
        State::cost = cost;
        State::trailcost = trailcost;
    }

//    bool operator==(State<T>* other){
//        if(this == other){
//            return true;
//        }else{
//            return false;
//        }
//    }
    //destructor
    ~State() {
    };

    double getHeuri() const {
        return this->heuri;
    }

    void setHeuri(double heuri) {
        State::heuri = heuri;
    }

    bool operator<(const State &otherState) {
        //compare the cost of the state
        if (otherState.getCost() < this->cost) {
            return true;
        } else {
            return false;
        }
    }

    bool operator>(const State &otherState) {
        //compare the cost of the state
        if (otherState.getCost() > this->cost) {
            return true;
        } else {
            return false;
        }
    }


};

#endif //PROJECT2_STATE_H
