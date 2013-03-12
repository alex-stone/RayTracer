#ifndef COLOR_H
#define COLOR_H

//****************************************************
// Color Header Definition
//****************************************************

class Color {
  private:
    float r, g, b;

  public:
    Color();
    Color(float x, float y, float z);

    float getR() {return r; };
    float getG() {return g; };
    float getB() {return b; };

    void setR(float x);
    void setG(float y);
    void setB(float z);

    Color* coefficientScale(Color* col);

    int getRgbRed();
    int getRgbGreen();
    int getRgbBlue();

    float clipValue(float x);
    
    void print();
    void add(Color* col);

    Color copy();

};

#endif
