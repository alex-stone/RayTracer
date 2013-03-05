#ifndef LOCALGEO_H
#define LOCALGEO_H

#include "Coordinate.h"
#include "Vector.h"

//****************************************************
// LocalGeo Header Definition
//****************************************************

class LocalGeo {
  private:
    Coordinate* position;
    Vector* normal;

  public:
    LocalGeo(Coordinate* pos, Vector* norm);

};

#endif
