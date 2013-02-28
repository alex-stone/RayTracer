
#include <iostream>
#include <time.h>
#include <math.h>
#include "Coordinate.h"


Coordinate::Coordinate() {
  setCoordinate(0.0f, 0.0f, 0.0f);
}

Coordinate::Coordinate(float a, float b, float c) {
  setCoordinate(a, b, c);
}

void Coordinate::setCoordinate(float a, float b, float c) {
  x = a;
  y = b;
  z = c;
}





