
#include <iostream>
#include <time.h>
#include <math.h>
#include "Coordinate.h"

using namespace std;

//****************************************************
// Coordinate Class
//****************************************************

Coordinate::Coordinate() {
    setCoordinate(0.0f, 0.0f, 0.0f);
}

Coordinate::Coordinate(float a, float b, float c) {
    this->x = a;
    this->y = b;
    this->z = c;
}

void Coordinate::setCoordinate(float a, float b, float c) {
    this->x = a;
    this->y = b;
    this->z = c;
}

float Coordinate::distTo(Coordinate* pos) {
    return sqrt(pow(pos->getX() - this->x, 2) + pow(pos->getY() - this->y, 2) + pow(pos->getZ() - this->z, 2) ) ;
}

void Coordinate::print() {
    cout << "(" << this->x << "," << this->y << "," << this->z << ")" << endl;
}

Coordinate* Coordinate::getCopy() {
    Coordinate* temp = new Coordinate(this->x, this->y, this->z);
    return temp;
}

Vector* Coordinate::vectorTo(Coordinate* pos) {
    Vector* vec = new Vector(pos->getX() - this->x, pos->getY() - this->y, pos->getZ() - this->z);
    return vec;
}

Vector* Coordinate::vectorFromOrigin() {
    Vector* vec = new Vector(this->x, this->y, this->z);
    return vec;
}

/*
int main(int argc, char* argv[]) {
    Coordinate* test = new Coordinate(0.4f, 0.2f, -0.5f);

    test->print();

    // Add more functions to test out

    Coordinate* pos1 = new Coordinate(2.0f, 5.0f, -3.0f);
    Coordinate* pos2 = new Coordinate(1.0f, 10.0f, 2.0f);

    pos1->print();
    pos2->print();

    Vector* vec = pos1->vectorTo(pos2);

    vec->print();


}

*/


