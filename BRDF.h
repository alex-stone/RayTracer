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

  public:
    BRDF(Color* diffuse, Color* specular, Color* ambient, Color* reflection);

    Color* getKD(){ return kd; };
    Color* getKS(){ return ks; };
    Color* getKA(){ return ka; };
    Color* getKR(){ return kr; };

};

#endif
