#include <iostream>
#include <math.h>
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
    float length = sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));    

    cout << "LENGTH = " << length << endl;

    this->x = x/length;
    this->y = y/length;
    this->z = z/length; 
} 

void Vector::scale(float scale) {
    this->x *= scale;
    this->y *= scale;
    this->z *= scale;
}

void Vector::add(Vector* v) {
    this->x += v->getX();
    this->y += v->getY();
    this->z += v->getZ();
}

void Vector::sub(Vector* v) {
    this->x -= v->getX();
    this->y -= v->getY();
    this->z -= v->getZ();
}

float Vector::dot(Vector* v) {
    return ((this->x * v->getX()) + (this->y * v->getY()) + (this->z * v->getZ()));
}

void Vector::print() {
    cout << "[" << this->x << ", " << this->y << ", " << this->z << "]" << endl;

}

int main(int argc, char* argv[]) {
    Vector* vec1 = new Vector(3.0f, 2.0f, 4.0f);
    Vector* vec2 = new Vector(2.0f, -3.0f, -2.0f);
    Vector* vec3 = new Vector(1.0f, 2.0f, -1.0f);

    cout << "Vector 1: " << endl;
    vec1->print();

    cout << "Vector 1 Scale by -2" << endl;
    vec1->scale(-2.0f);
    vec1->print();

    cout << "Vector 1 Normalized" << endl;
    vec1->normalize();
    vec1->print();

    cout << "Vector 2: " << endl;
    vec2->print();

    cout << "Vector 3: " << endl;
    vec3->print();

    cout << "Vec2 + vec3: " << endl;
    vec2->add(vec3);
    vec2->print();
 
    cout << "Result - Vec3: " << endl;
    vec2->sub(vec3);
    vec2->print();

    cout << "Result dot vec3 = " << vec2->dot(vec3) << endl;


}


