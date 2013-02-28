#include <iostream>
#include "Camera.h"

using namespace std;

//****************************************************
// Camera Class
//****************************************************

Camera::Camera() {

}

Camera::Camera(Coordinate ep, Coordinate UL, Coordinate UR, Coordinate LR, Coordinate LL, int h, int w) {
    eyePosition = ep;
    upperLeft = UL;
    upperRight = UR;
    lowerRight = LR;
    lowerLeft = LL;
    pixelHeight = h;
    pixelWidth = w;

}

Coordinate Camera::pixelToCoordinate(int x, int y) {
        

}

