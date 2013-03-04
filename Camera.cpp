#include <iostream>
#include "Camera.h"

using namespace std;

//****************************************************
// Camera Class
//****************************************************

Camera::Camera(int h, int w) {
    eyePosition = new Coordinate (0,0,0);
    upperLeft = new Coordinate(-1, 1, -1);
    upperRight = new Coordinate(1, 1, -1);
    lowerRight = new Coordinate(1, -1, -1);
    lowerLeft = new Coordinate(-1, -1, -1);

    pixelHeight = h;
    pixelWidth = w;
}

Camera::Camera(Coordinate* ep, Coordinate* UL, Coordinate* UR, Coordinate* LR, Coordinate* LL, int h, int w) {
    eyePosition = ep;
    upperLeft = UL;
    upperRight = UR;
    lowerRight = LR;
    lowerLeft = LL;
    pixelHeight = h;
    pixelWidth = w;

}

Vector* Camera::pixelToVector(int x, int y) {
    Vector* horiz = upperLeft->vectorTo(upperRight);
    Vector* vert = upperLeft->vectorTo(lowerLeft);

    float scaleHoriz = ((float) x) / ((float) pixelWidth);
    float scaleVert = ((float) y) / ((float) pixelHeight);

    horiz->scale(scaleHoriz);
    vert->scale(scaleVert);
    
    Vector* returnVec = new Vector(upperLeft->getX(), upperLeft->getY(), upperLeft->getZ());

    returnVec->add(horiz);
    returnVec->add(vert);

    return returnVec;
}

Ray* Camera::generateRay(Sample& samp) {
    // Create a ray with position = eyePosition, and direction = vector from ep to pixel
    
    Ray* r = new Ray(this->eyePosition, this->pixelToVector(samp.getX(), samp.getY()));
    return r;

}

int main (int argc, char* argv[]) {
    Camera* cam = new Camera(100, 100);

    Vector* vec1 = cam->pixelToVector(50,0); 
    Vector* vec2 = cam->pixelToVector(0, 50);
    Vector* vec3 = cam->pixelToVector(50, 50);
    Vector* vec4 = cam->pixelToVector(100, 50);
    Vector* vec5 = cam->pixelToVector(50, 100);
    Vector* vec6 = cam->pixelToVector(25, 25);
    Vector* vec7 = cam->pixelToVector(75, 50);



    cout << "(50, 0): " << endl;
    vec1->print();


    cout << "(0, 50): " << endl;
    vec2->print();

    cout << "(50, 50): " << endl;
    vec3->print();

    cout << "(100, 50): " << endl;
    vec4->print();

    cout << "(50, 100): " << endl;
    vec5->print();

    cout << "(25, 25): " << endl;
    vec6->print();

    cout << "(75, 50): " << endl;
    vec7->print();





}


