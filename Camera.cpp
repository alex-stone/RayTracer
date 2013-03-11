#include <iostream>
#include <math.h>
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

Camera::Camera(Coordinate* lookfrom, Coordinate* lookat, Vector* up, float fovVert, int h, int w) {
    // lookFrom = eyePosition
    // lookat -> Center of the Image Plane
    // up Vector is 
    // fov is in degrees
    // aspectRation = width/height

    // tan (fovVert / 2) = (ImageHeight/2) / d   and d = 1
    // ImageHeight = 2 * tan (fovVert / 2)

    eyePosition = lookfrom;
    Coordinate* center = lookat;

    // aspectRatio = tan(fovHoriz/2) / tan(fovVert/2)
    // tan(fovHoriz/2) = ImageHeight / 2

    aspectRatio = (float) w / (float) h;

    float imageHeight = 2 * tan(fovVert / 2);
    float fovHoriz = 2 * atan(aspectRatio * imageHeight / 2);
    float imageWidth = 2 * tan(fovHoriz / 2);
    // float imageWidth = aspectRatio * imageHeight;

    Vector* view = lookfrom->vectorTo(lookat);
    Vector* upVec = up->getCopy();
    upVec->normalize();
    upVec->scale(imageHeight/2);

    Vector* rightVec = up->cross(view);
    rightVec->normalize();
    rightVec->scale(imageWidth/2);
   
    Coordinate* upperMid = center->addVector(upVec);
    Coordinate* lowerMid = center->addVector(upVec->getOpposite());
    
    upperLeft  = upperMid->addVector(rightVec->getOpposite());
    upperRight = upperMid->addVector(rightVec);
    lowerLeft  = lowerMid->addVector(rightVec->getOpposite());
    lowerRight = lowerMid->addVector(rightVec);
    pixelHeight = h;
    pixelWidth = w;

    upperLeft->print();
    upperRight->print();
    lowerRight->print();
    lowerLeft->print();

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

Ray* Camera::generateRay(Sample* samp) {
    // Create a ray with position = eyePosition, and direction = vector from ep to pixel
    
    Ray* r = new Ray(this->eyePosition, this->pixelToVector(samp->getX(), samp->getY()));
    return r;

}
/*
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

*/
