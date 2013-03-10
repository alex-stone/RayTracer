#include <iostream>
#include <math.h>
#include "Triangle.h"
#include "Vector.h"
#include "LocalGeo.h"
#include "Coordinate.h"
#include "Ray.h"


//****************************************************
// Triangle Class Definition
//****************************************************

Triangle::Triangle(Coordinate* vec1, Coordinate* vec2, Coordinate* vec3) {
    v1 = vec1;
    v2 = vec2;
    v3 = vec3;

    // Normal = Cross Product of (v2 - v1) and (v3 - v1)

    Vector* vector1 = v1->vectorTo(v2);
    Vector* vector2 = v1->vectorTo(v3);

    normal = vector1->cross(vector2);
    normal->normalize();
}

//****************************************************
// BaryCentric Coordinates:   Start from point A, and go a certain amount along AC, and a certain amount AB
//      P = A + x * AC + y * AB
//      Solve for x,y
//          if x > 1 or y > 1, not in triangle, if x + y > 1, not in triangle

//      (pointInPlane - A) = x * AC + y * AB
//      v3 = x * v1 + y * v2
//      v1 = C - A
//      v2 = B - A
//      v3 = P - A
// 
//      v3 . v1  =  x * (v1 . v1) + y * (v2 . v1)    - Dot product of v1 on both sides
//      v3 . v2  =  x * (v1 . v2) + y * (v2 . v2)    - Dot product of v2 on both sides
//
//      x = ((v2 . v2) * (v3 . v1) - (v2 . v1) (v3 . v2)) / ((v1 . v1) * (v2 . v2) - (v1 . v2)*(v2 . v1))
//      y = ((v1 . v1) * (v3 . v2) - (v1 . v2) (v3 . v1)) / ((v1 . v1) * (v2 . v2) - (v1 . v2)*(v2 . v1))
//****************************************************
bool Triangle::isPointInTriangle(Coordinate* pointInPlane) {
    Vector* vector1 = v1->vectorTo(v3);
    Vector* vector2 = v1->vectorTo(v2);
    Vector* vector3 = v1->vectorTo(pointInPlane);

    float dot11 = vector1->dot(vector1);
    float dot12 = vector1->dot(vector2);
    float dot13 = vector1->dot(vector3);
    float dot22 = vector2->dot(vector2);
    float dot23 = vector2->dot(vector3);
    float dot33 = vector3->dot(vector3);
    float denom = dot11*dot22 - dot12*dot12;

    float x = (dot22 * dot13 - dot12 * dot23) / denom;
    float y = (dot11 * dot23 - dot12 * dot13) / denom;

    if(x > 1.0f || y > 1.0f || x + y > 1.0f || x < 0.0f || y < 0.0f) {
        return false;

    } else {
        return true;
    }
}

//****************************************************
// Triangle Intersection Test:
//	Test if Ray intersects with plane of triangle
//  	If so, is that intersection pt, within the
//		triangle.
//	Ray: 	P = origin + t*direction
//      Plane:  (p - p0) dot n = 0
// 		
//	(t*dir + origin - p0) dot n = 0
//	t * (dir dot n) = - (origin - p0)
//	t = (p0 - l0) dot n / ( dir dot n)
//****************************************************
LocalGeo* Triangle::intersect(Ray* ray) {
    // Detect if Ray intersects the plane formed by those 3 vertices

    // Vector for (p0 - l0):
    Vector* originToTriangle = ray->getPosition()->vectorTo(v1);
    float numerator = originToTriangle->dot(normal);    
    float denominator = ray->getDirection()->dot(normal);
   
    
    // When the Denominator is 0 / extremely close to 0, then its parallel to plane
    
    if(denominator < 0.000001  && denominator > -0.000001) {
	   std::cout << "Denominator Test Failed" << std::endl;
	   return NULL;	// On Plane or parallel to Plane
    } 

    float distance = numerator / denominator;  
    // Then Triangle is behind the Ray
    if (distance < 0.0f) {
        std::cout << "Distance Test Failed w/ dist = " << distance << std::endl;
	    return NULL;
    }

    Coordinate* pointInPlane = ray->getPointFromDist(distance);

    if(!isPointInTriangle(pointInPlane)) {
        return NULL;
    }

    LocalGeo* loc = new LocalGeo(pointInPlane, normal);

    return loc;


}

bool Triangle::intersectP(Ray* ray) {
    // Vector for (p0 - l0):
    Vector* triangleToOrigin = v1->vectorTo(ray->getPosition());
    float numerator = triangleToOrigin->dot(normal);    
    float denominator = ray->getDirection()->dot(normal);
   
    
    // When the Denominator is 0 / extremely close to 0, then its parallel to plane
    
    if(denominator < 0.000001  || denominator > -0.000001) {
        return false;    // On Plane or parallel to Plane
    } 

    float distance = numerator / denominator;  
    // Then Triangle is behind the Ray
    if (distance < 0.0f) {
        return false;
    }

    Coordinate* pointInPlane = ray->getPointFromDist(distance);

    return isPointInTriangle(pointInPlane);
}



