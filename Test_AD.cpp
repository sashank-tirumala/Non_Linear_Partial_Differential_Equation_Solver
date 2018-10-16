#include<iostream>
#include <cmath>
#include"AD.h"

using namespace std;
void test_plus_and_minus()
{
  AD<int> h(1,2,3);
  AD<int> g(4,5,6);
  AD<int> i(5,7,9);
  int a = 23;
  AD<int> temp = h;
  AD<int> q = +temp;
  if(q == h)
  {
    cout<<"+AD passed"<<endl;
  }
  else
  {
    cout<<"+AD not passed"<<endl;
  }
  AD<int>w(-1,-2,-3);
  temp = -h;
  if(w == temp)
  {
    cout<<"-AD passed"<<endl;
  }
  else
  {
    cout<<"-AD not passed"<<endl;
  }
  temp = h+g;
  if(i == temp)
    {
    cout<<"AD + AD passed"<<endl;
    }
   else
   {
    cout<<"AD + AD not passed"<<endl;
   }
   temp = i + a;
   AD<int> j(28,7,9);
   if(j == temp)
   {
     cout<<"AD + T passed"<<endl;
   }
   else
   {
     cout<<"AD + T not passed"<<endl;
   }
   temp = a + i;
   if(j == temp)
   {
     cout<<"T + AD passed"<<endl;
   }
   else
   {
     cout<<"T + AD not passed"<<endl;
   }
   temp = h -g;
   AD<int> ans1(-3, -3,-3);
   if(ans1 == temp)
   {
     cout<<"AD - AD passed"<<endl;
   }
   else
   {
     cout<<"AD - AD not passed"<<endl;
   }

   temp = h - a;
   AD<int> ans2(-22,2,3);
   if(ans2 == temp)
   {
     cout<<"AD - T passed"<<endl;
   }
   else
   {
     cout<<"AD - T not passed"<<endl;
   }
   temp = a-h;
   AD<int> ans3(22,-2,-3);
   if(ans3 == temp)
   {
     cout<<"T - AD passed"<<endl;
   }
   else
   {
     cout<<"T - AD not passed"<<endl;
   }


}

void test_multi_and_divi()
{
  AD<float> a(1,0.5,0.25);
  AD<float> b(-1,-1,-1);

  AD<float>c(-1,-1.5,-2.25);
  AD<float> temp = a*b;
  if(c == temp)
  {
    cout<<"AD*AD passed"<<endl;
  }
  else
  {
    cout<<"AD*AD not passed"<<endl;
  }
  AD<float> d(2,1,0.5);
  temp = a*2;
  if(d == temp)
  {
    cout<<"AD*T passed"<<endl;
  }
  else
  {
    cout<<"AD*T not passed"<<endl;
  }
  AD<float> e(2,1,0.5);
  temp = (float)2*a;
  if(e == temp)
  {
    cout<<"T*AD passed"<<endl;
  }
  else
  {
    cout<<"T*AD not passed"<<endl;
  }
  AD<int> n1(1,4,12);
  AD<int> n2(1,2,2);
  AD<int> n3(1,2,2);
  AD<int> temp1 = n1/n2;
  if(n3 == temp1)
  {
    cout<<"AD/AD passed"<<endl;
  }
  else
  {
    cout<<"AD/AD not passed"<<endl;
  }
  AD<int> n4(1,-2,6);
  temp1 = 1/n2;
  if(n4 == temp1)
  {
    cout<<"T/AD passed"<<endl;
  }
  else
  {
    cout<<"T/AD not passed"<<endl;
  }
  AD<int> n5(1,2,2);
  temp1 = n2/1;
  if(n5 == temp1)
  {
    cout<<"AD/T passed"<<endl;
  }
  else
  {
    cout<<"AD/T not passed"<<endl;
  }
}
//
void test_powers_and_logs()
{
  AD<double>n1(1,1,0);
  AD<double>n2(1,2,2);
  AD<double> temp = n1^2;
  if(n2 == temp)
  {
    cout<<"AD^T passed"<<endl;
  }
  else
  {
    cout<<"AD^T not passed"<<endl;
  }
  temp = 2.0^n1;
  AD<double>n3(2,2*log(2),2*log(2)*log(2));
  if(n3 == temp)
  {
    cout<<"T^AD passed"<<endl;

  }
  else
  {
    cout<<"T^AD not passed"<<endl;
    temp.disp();
  }
  AD<double> n4(0,2,-2);
  temp = log(n2);
  if(n4 == temp)
  {
      cout<<"log(AD) passed"<<endl;
  }
  else
  {
    cout<<"log(AD) not passed"<<endl;
  }
  AD<double> n5(exp(1),2*exp(1),6*exp(1));
  temp = exp(n2);
  if(n5 == temp)
  {
      cout<<"e^AD passed"<<endl;
  }
  else
  {
    cout<<"e^AD not passed"<<endl;
  }

}
void test_trig()
{
 AD<double> n1(0,0,2);
 AD<double> temp= asin(n1);
 AD<double> n2(0,0,2);
 if(n2 == temp)
 {
     cout<<"asin(AD) passed"<<endl;
 }
 else
 {
   cout<<"asin(AD) not passed"<<endl;
 }

 temp= acos(n1);
 AD<double> n3(acos(0),0,2);
 if(n3 == temp)
 {
     cout<<"acos(AD) passed"<<endl;
 }
 else
 {
   cout<<"acos(AD) not passed"<<endl;
 }

 temp= atan(n1);
 AD<double> n4(0,0,2);
 if(n4 == temp)
 {
     cout<<"atan(AD) passed"<<endl;
 }
 else
 {
   cout<<"atan(AD) not passed"<<endl;

 }

 temp= sinh(n1);
 AD<double> n5(0,0,2);
 if(n5 == temp)
 {
     cout<<"sinh(AD) passed"<<endl;
 }
 else
 {
   cout<<"sinh(AD) not passed"<<endl;

 }

 temp= cosh(n1);
 AD<double> n6(1,0,0);
 if(n6 == temp)
 {
     cout<<"cosh(AD) passed"<<endl;
 }
 else
 {
   cout<<"cosh(AD) not passed"<<endl;
 }

 temp= asinh(n1);
 AD<double> n7(asinh(0),0,2);
 if(n7 == temp)
 {
     cout<<"asinh(AD) passed"<<endl;
 }
 else
 {
   cout<<"asinh(AD) not passed"<<endl;
 }
 temp = acosh(n1);
 AD<double> n8(acosh(0),0,-2);
 if(n8 == temp)
 {
     cout<<"acosh(AD) passed"<<endl;
 }
 else
 {
   cout<<"acosh(AD) not passed"<<endl;
 }
// tanh works fine. infi became NaN
}


int main()
{
  test_plus_and_minus();
  test_multi_and_divi();
  test_powers_and_logs();
  test_trig();


}
