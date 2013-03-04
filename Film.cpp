#include <iostream>
#include "FreeImage.h"
#include "Film.h"
#include "Sample.h"
#include "Color.h"

using namespace std;

//****************************************************
// Film Class
//****************************************************

Film::Film() {
    setSize(480, 640);
    pixelBucket = new Color*[480];
    for(int i = 0; i < pixelWidth; i++) {
        pixelBucket[i] = new Color[640];
    }
 
}

Film::Film(int h, int w) {
    setSize(h, w);
    pixelBucket = new Color*[w];	// Note Color 2D array is [width][height]
    for(int i = 0; i < pixelWidth; i++) {
       	pixelBucket[i] = new Color[h];
    }
}

void Film::setSize(int h, int w) {
    pixelHeight = h;
    pixelWidth = w;
}

void Film::commit(Sample samp, Color color) {
    pixelBucket[samp.getX()][samp.getY()] = color;
}

void Film::writeImage() {
    // Do Stuff

    // Note: Bitmaps have their origin (0, 0) at bottom left, and our (0,0) is top left

    FreeImage_Initialise();
    
    FIBITMAP* bitmap = FreeImage_Allocate(pixelWidth, pixelHeight, 24);
    RGBQUAD color;
    Color* bucketColor;

    // Iterate through pixelBucket and do FreeImage.SetPixelColor
    for(int i = 0; i < pixelWidth; i++) {
        for(int j = 0; j < pixelHeight; j++) {
	    bucketColor = &pixelBucket[i][pixelHeight - 1 - j];

	    color.rgbRed = bucketColor->getR();
	    color.rgbGreen = bucketColor->getG();
	    color.rgbBlue = bucketColor->getB();
	    
	    FreeImage_SetPixelColor(bitmap, i, j, &color);
        }

    } 

    if (FreeImage_Save(FIF_PNG, bitmap, "test.png", 0))
	cout << "Image Successfuly Saved!" << endl;

    FreeImage_DeInitialise();

}

int main(int argc, char* argv[]) {
    Film* f = new Film(400, 900);

    f->writeImage();

    cout << "Film Main Function Ran" << endl;
}

