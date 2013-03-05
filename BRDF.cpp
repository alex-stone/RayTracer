#include <iostream>
#include "BRDF.h"
#include "Color.h"

//****************************************************
// BRDF  Definition
//****************************************************

BRDF::BRDF(Color* diffuse, Color* specular, Color* ambient, Color* reflection) {
    kd = diffuse;
    ks = specular;
    ka = ambient;
    kr = reflection
}

