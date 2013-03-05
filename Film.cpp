#include <iostream>
#include <math.h>
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
    // Note that FreePixel's Blue and Red are switched.
    for(int i = 0; i < pixelWidth; i++) {
        for(int j = 0; j < pixelHeight; j++) {
	    bucketColor = &pixelBucket[i][pixelHeight - 1 - j];

	    color.rgbRed = bucketColor->getRgbBlue();
	    color.rgbGreen = bucketColor->getRgbGreen();
	    color.rgbBlue = bucketColor->getRgbRed();
	    
	    FreeImage_SetPixelColor(bitmap, i, j, &color);
        }

    } 

    if (FreeImage_Save(FIF_PNG, bitmap, "test.png", 0))
	cout << "Image Successfuly Saved!" << endl;

    FreeImage_DeInitialise();

}

void Film::circleTest() {
    Color* red = new Color(0.0f, 0.0f, 1.0f);

    float radius = min(pixelHeight, pixelWidth) * 0.4444f;

    for (int i = 0; i < pixelWidth; i++) {
        for(int j = 0; j < pixelHeight; j++) {

	    float x = (i + 0.5 - (pixelWidth/2));
	    float y = (j + 0.5 - (pixelHeight/2));

   	    float dist = sqrt(x*x + y*y);
	    
  	    if( dist <= radius) {
		cout << "Dist <= Radius " << endl;
		pixelBucket[i][j].add(red); 
	    } 
 
        }
    }
	
    cout << "Circle Test Ran" << endl;

}

int main(int argc, char* argv[]) {
    Film* f = new Film(400, 900);
    f->circleTest();

    f->writeImage();

    cout << "Film Main Function Ran" << endl;
}

