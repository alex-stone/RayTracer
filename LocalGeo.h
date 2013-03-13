#ifndef LOCALGEO_H
#define LOCALGEO_H

#include "Coordinate.h"
#include "Vector.h"
#include "Transformation.h"
#include "LocalGeo.h"

//****************************************************
// LocalGeo Header Definition
//****************************************************

class LocalGeo {
  private:
    Coordinate* position;
    Vector* normal;

  public:
    LocalGeo(Coordinate* pos, Vector* norm);

    //Getters
    Coordinate* getPosition() { return position; };
    Vector* getNormal() { return normal; };

    LocalGeo* applyTransformation(Transformation* transform);
    LocalGeo* applyInverseTransformation(Transformation* transform);

};

#endif
