#ifndef BRDF_H
#define BRDF_H
#include "Color.h"

//****************************************************
// BRDF Header Definition
//****************************************************

class BRDF {
  private:
    Color* kd;
    Color* ks;
    Color* ka;
    Color* kr;
    float sp;

  public:
    BRDF(Color* diffuse, Color* specular, Color* ambient, Color* reflection, float spec);

    Color* getKD(){ return kd; };
    Color* getKS(){ return ks; };
    Color* getKA(){ return ka; };
    Color* getKR(){ return kr; };
    float getSP() { return sp; };
};

#endif
