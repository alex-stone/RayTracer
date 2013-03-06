#ifndef POINTLIGHT_H
#define POINTLIGHT_H

//****************************************************
// PointLight Header Definition
//****************************************************

class PointLight : public Light {
  private:
    Coordinate* point;
    Color* color;

  public:
    PointLight(Coordinate* pos, Color* col);
    Ray* generateLightRay(LocalGeo* loc);
    Color* getColor() { return color; };

};

#endif
