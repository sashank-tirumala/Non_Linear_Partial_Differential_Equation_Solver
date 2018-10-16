#include<iostream>
#include"Jacobian.cpp"
using namespace std;

int main()
{
  AD<double> a(1.0,2.0,3.0);
  AD<double> b(4.0,5.0,6.0);
  AD<double> c[2] = {a,b};
  exp1<AD<double>> q1,q2,q3;
  exp1<AD<double>> q_arr[3] = {q1,q2,q3};
  Jacobian<exp1<AD<double>>,3> j1(q_arr);
  j1.f1[1](c).disp();

}
