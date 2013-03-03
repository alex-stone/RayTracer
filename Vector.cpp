#include <iostream>
#include "Vector.h"


using namespace std;

//****************************************************
// Vector Class
//****************************************************


Vector::Vector(float a, float b, float c) {
    x = a;
    y = b;
    z = c;
}

void Vector::normalize() {
    float length = sqrt(this->x * this->x + this->y * this->y + this->z + this->z);    

    this->x = x/length;
    this->y = y/length;
    this->z = z/length; 
} 

void Vector::scale(float scale) {
    if( scale >= 0 ) {
    	this->x *= scale;
    	this->y *= scale;
    	this->z *= scale;
    }
}

void Vector::add(Vector v) {
    this->x += v.getX();
    this->y += v.getY();
    this->z += v.getZ();
}

void Vector::sub(Vector v) {
    this->x -= v.getX();
    this->y -= v.getY();
    this->z -= v.getZ();
}

float Vector::dot(Vector v) {
    return ((this->x * v.getX()) + (this->y * v.getY()) + (this->z * v.getZ()))
}



