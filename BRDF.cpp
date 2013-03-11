#include <iostream>
#include "BRDF.h"
#include "Color.h"

//****************************************************
// BRDF  Definition
//****************************************************

BRDF::BRDF(Color* diffuse, Color* specular, Color* ambient, Color* reflection, float* spec) {
    kd = diffuse;
    ks = specular;
    ka = ambient;
    kr = reflection;
    sp = spec;
}

