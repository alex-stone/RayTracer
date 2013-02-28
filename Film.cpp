#include <iostream>
#include "film.h"

using namespace std;

//****************************************************
// Film Class
//****************************************************

Film::Film() {
    setSize(480, 640);
    pixelBucket = new Color[480][640];
}

Film::Film(int h, int w) {
    setSize(h, w);
    pixelBucket = new Color[h][w];
}

void Film::setSize(int h, int w) {
    pixelHeight = h;
    pixelWidth = w;
}

void Film::commit(Sample samp, Color color) {
    pixelBucket[samp.getY()][samp.getX()] = color;
}

void Film::writeImage() {
    // Do Stuff
}
