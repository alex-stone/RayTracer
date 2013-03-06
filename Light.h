#ifndef LIGHT_H
#define LIGHT_H

//****************************************************
// Light Header Definition
//****************************************************

class Light {

  public:
    virtual Ray* generateLightRay(LocalGeo* loc)=0;
    virtual Color* getColor() = 0;

};
#endif
