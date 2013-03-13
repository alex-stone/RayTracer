#include <iostream>
#include "LocalGeo.h"

//****************************************************
// Local Geo Class Definition
//****************************************************

LocalGeo::LocalGeo(Coordinate* pos, Vector* norm) {
    position = pos;
    norm->normalize();
    normal = norm;
}

LocalGeo* LocalGeo::applyTransformation(Transformation* transform) {
    Coordinate* pos = transform->getMatrix()->transformPt(position);

    LocalGeo* loc = new LocalGeo(pos,this->normal );
 
    return loc;
}  

LocalGeo* LocalGeo::applyInverseTransformation(Transformation* transform) {
    Coordinate* pos = transform->getInverseTransformation()->transformPt(position);

    LocalGeo* loc = new LocalGeo(pos,this->normal);
 
    return loc;
}  




