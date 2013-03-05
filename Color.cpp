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

void Color::add(Color* col) {
    this->r = clipValue(col->r + this->r);
    this->g = clipValue(col->g + this->g);
    this->b = clipValue(col->b + this->b);
}

int Color::getRgbRed() {
    return clipValue(this->r) * 255;
}

int Color::getRgbGreen() {
    return clipValue(this->g) * 255;
}

int Color::getRgbBlue() {
    return clipValue(this->b) * 255;
}

//string Color::toString() {
    //return returnString;
//}

void Color::print() {
    cout << "[" << this->r << ", " << this->g << ", " << this->b << "]" << endl;
}
/*
int main(int argc, char *argv[]) {
    Color* col1 = new Color(0.5f, 0.3f, 0.2f);
    Color* col2 = new Color(0.6f, 0.5f, 0.0f);
   
    col1->print();
    col2->print();
    col2->add(col1);
    col2->print();
 
    return 1;
}
*/
