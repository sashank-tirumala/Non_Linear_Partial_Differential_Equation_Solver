#include<iostream>
#include"AD.h"
using namespace std;
template<class T>
class Base_exp
{
public:
  virtual void operator()();
};

template<class T>
class exp1 : Base_exp<T>
{
public:
  T operator()(T *a)
  {
    T res;
    res = 1.0 + a[0]*a[1];
    return res;
  }
};
template<class T>
class exp3 : Base_exp<T>
{
public:
  T operator()(T *a)
  {
    T res;
    res = 1.0 - a[0]*a[1];
    return res;
  }
};

// using expPtr = AD<double>(*)(AD<double>*);
// namespace expressions
// {
// AD<double> f1(AD<double> *x)
// {
//   AD<double> res;
//   res= 1.0 + x[0]*x[1];
//   return res;
// }
// }

//
int main()
{
  // AD<double> a(1.0,2.0,3.0);
  // AD<double> b(4.0,5.0,6.0);
  // AD<double> c[2] = {a,b};
  // Base_exp<AD<double>> *q;
  // exp1<AD<double>> ex1;
  // exp3<AD<double>> ex2;
  // q = &ex1;
  // AD<double> res = q->operator()(c);
  // res.disp();
  AD<int> a(1,3,4);
  AD<int> ab[2] = {a,a};
  cout<<ab[0];
}
