
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

void Coordinate::print() {
    cout << "(" << this->x << "," << this->y << "," << this->z << ")" << endl;
}

Coordinate* Coordinate::getCopy() {
    Coordinate* temp = new Coordinate(this->x, this->y, this->z);
    return temp;
}

/*
int main(int argc, char* argv[]) {
    Coordinate* test = new Coordinate(0.4f, 0.2f, -0.5f);

    test->print();

    // Add more functions to test out

}
*/



