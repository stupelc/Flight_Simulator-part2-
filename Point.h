//
// Created by almogg on 1/9/19.
//

#ifndef PROJECT2_POINT_H
#define PROJECT2_POINT_H

#include <ostream>
#include <fstream>
#include <string>
#include <iostream>

using std::string;
using std::ostream;
using std::istream;

class Point {
private:
    int x;
    int y;
    double val;
public:
    Point(int x, int y);

    Point(){}
    ~Point();

    //get x value
    int getX() const;

    //set x value
    void setX(int x);

    //get y value
    int getY() const;

    //set y value
    void setY(int y);

    //return true if both points equals-else otherwise
    bool equal(Point other);

    //return true if one point equals to another one
    bool operator==(Point other);

    //return 'true' if the other point is left neighbor
    bool isLeftNeighbor(Point other);

    //return 'true' if the other point is right neighbor
    bool isRightNeighbor(Point other);

    //return 'true' if the other point is up neighbor
    bool isUpNeighbor(Point other);

    //return 'true' if the other point is down neighbor
    bool isDownNeighbor(Point other);

    //get the type step that we did
    string getMove(Point other);

    //get other point and calculate diatance between them
    double distance(Point other);

    //print a point using ostream
    friend ostream &operator<<(ostream &out, const Point &point);
    friend istream &operator>>(istream &in,  Point &point){
    char brack1 = '(',brake2 = ')', comma = ',';
    string str;
   // string x,y;
  // int x,y;
    in >> brack1 >> point.x >> comma >> point.y>>str>>brake2;
    return in;
    };

};

#endif //PROJECT2_POINT_H
