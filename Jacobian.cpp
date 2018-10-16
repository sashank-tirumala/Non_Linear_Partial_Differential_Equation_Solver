#include<iostream>
#include<cmath>
#include"Expressions.cpp"
template<class T, int n>
class Jacobian
{
private:
  int size;
public:
  T *f1;
  Jacobian(){};
  Jacobian(T *df1): size(n)
  {
    f1 = df1;
  }
};
