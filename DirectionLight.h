#ifndef DIRECTIONLIGHT_H
#define DIRECTIONLIGHT_H

#include "Light.h"
#include "Color.h"
#include "Ray.h"
#include "Vector.h"
#include "Coordinate.h"

//****************************************************
// DirectionLight Header Definition
//****************************************************

class DirectionLight : public Light {
  private:
    Vector* direction;
    Color* color;

  public:
    DirectionLight(Vector* dir, Color* col);
    Color* getColor() { return color; };
    bool isPointLight() { return false; };

    Ray* generateLightRay(Coordinate* pt);
    Vector* getDirection() { return direction; };
    Vector* getLightDirection(Coordinate* pt);
    Coordinate* getPosition() { return NULL; };

};


#endif
