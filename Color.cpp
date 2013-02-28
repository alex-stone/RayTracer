#include <iostream>
#include "Color.h"

using namespace std;

//****************************************************
// Color Class
//****************************************************

Color::Color() {
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
}

Color::Color(float x, float y, float z) {
    r = clipValue(x);
    g = clipValue(y);
    b = clipValue(z);

} 


float Color::clipValue(float x) {
    if(x > 1.0f) {
        return 1.0f;
    } else {
	if(x < 0.0f) {
	    return 0.0f;
	} else {
	    return x;
	}
    }
}
