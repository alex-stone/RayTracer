#ifndef DIRECTIONLIGHT_H
#define DIRECTIONLIGHT_H

#include "Vector.h"
#include "Color.h"
#include "Ray.h"

//****************************************************
// DirectionLight Header Definition
//****************************************************

class DirectionLight : public Light {
  private:
    Vector* direction;
    Color* color;

  public:
    DirectionLight(Vector* dir, Color* col);

    Ray* generateLightRay(localGeo* loc);
    Color* getColor() { return color; };

};

#endif
