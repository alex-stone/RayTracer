#include <iostream>
#include "Camera.h"

using namespace std;

//****************************************************
// Camera Class
//****************************************************

Camera::Camera() {

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
    Vector horiz = upperLeft.vectorTo(upperRight);
    Vector vert = upperLeft.vectorTo(lowerLeft);

    float scaleHoriz = ((float) x) / ((float) pixelWidth);
    float scaleVert = ((float) y) / ((float) pixelHeight);

    horiz.scale(scaleHoriz);
    vert.scale(scaleVert);
    
    Vector returnVec = new Vector(upperLeft.getX(), upperLeft.getY(), upperLeft.getZ());

    return returnVec;
}

