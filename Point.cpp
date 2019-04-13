//
// Created by almogg on 1/9/19.
//

#include "math.h"
#include "Point.h"

//constructor of a new point
Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

Point::~Point() {

}

int Point::getX() const {
    return x;
}

void Point::setX(int x) {
    Point::x = x;
}

int Point::getY() const {
    return y;
}

void Point::setY(int y) {
    Point::y = y;
}

//return 'true' if both points equals,'false' otherwise
bool Point::equal(Point other) {
    if ((this->getX() == other.getX()) && (this->getY() == other.getY()))return true;
    return false;
}

//return 'true' if the other point is left neighbor
bool Point::isLeftNeighbor(Point other) {
    if (this->x == other.getX() && this->y == (other.getY() - 1)) return true;
    return false;
}

//return 'true' if the other point is right neighbor
bool Point::isRightNeighbor(Point other) {
    if (this->x == other.getX() && this->y == (other.getY() + 1)) return true;
    return false;
}

//return 'true' if the other point is up neighbor
bool Point::isUpNeighbor(Point other) {
    if (this->x == (other.getX() - 1) && this->y == other.getY())return true;
    return false;
}

//return 'true' if the other point is down neighbor
bool Point::isDownNeighbor(Point other) {
    if (this->x == (other.getX() + 1) && this->y == other.getY())return true;
    return false;
}

//return true if one point equals to another one
bool Point::operator==(Point other) {
    if (this->x == other.x && this->y == other.y)return true;
    return false;
}

//get the type step that we did
string Point::getMove(Point other) {
    if (this->x == other.getX() && this->y > other.getY()) {
        return "Right";
    }
    if (this->x == other.getX() && this->y < other.getY()) {
        return "Left";
    }
    if (this->x > other.getX() && this->y == other.getY()) {
        return "Down";
    }
    if (this->x < other.getX() && this->y == other.getY()) {
        return "Up";
    }
}

double Point::distance(Point other) {
    double height, width, dis;
    height = abs(this->x - other.getX());
    width = abs(this->y - other.getY());
    dis = sqrt(pow(height, 2) + pow(width, 2)); //calculate the distance
    //height^2+width^2 -> sqrt all this
    return dis;
}

ostream &operator<<(ostream &out, const Point &point) {
    out << "(" << point.x << "," << point.getY() << ")";
    return out;
};

//istream& operator>>(istream &in, const Point &point) {
//    char brack1 = '(',brake2 = ')', comma = ',';
//   // string x,y;
//   int x,y;
//
////    return in >> brack1 >> point.x >> comma >> point.y>>brake2;
//}
//ostream& operator<<(ostream &out, const Point &point) {

//}