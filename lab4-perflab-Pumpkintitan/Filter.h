//-*-c++-*-
#ifndef _Filter_h_
#define _Filter_h_

using namespace std;

class Filter {
  //Reordered variables to maybe save space (i dont know if it actually does anything)
  int *data;
  int divisor;
  int dim;

public:
  Filter(int _dim);
  int get(int r, int c);
  void set(int r, int c, int value);

  int getDivisor();
  void setDivisor(int value);

  int getSize();
  void info();
};

#endif
