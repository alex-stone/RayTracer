#ifndef FILM_H
#define FILM_H

#include "Color.h"
#include "Sample.h"

//****************************************************
// Film Header Definition
//****************************************************

class Film {
  private:
    int pixelHeight;
    int pixelWidth;
    Color** pixelBucket;
    char* fileName;

  public:
    Film();
    Film(int h, int w, std::string file);
    
    void setSize(int h, int w);
  
    void commit(Sample* samp, Color* color); 
    void writeImage();

    void circleTest();

};

#endif
