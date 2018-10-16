#include<iostream>
#include"PDE.cpp"
using namespace std;

void test_get()
{
  double arr1[3][3]={{1.1, 2.1, 3.1},{1.1, 2.1, 3.1},{1.1, 2.1, 3.1}};
  double arr2[3]={1.0, 0.0, 1.0};
  PDE<double, 3> a(arr1, arr1, arr1, arr1, arr1, arr1, arr1, arr2, arr2, arr2, arr2);
  if(a.a_get(1,1)==2.1)
  {
    cout<<"a_get success"<<endl;
  }
  else
  {
    cout<<"a_get failure"<<endl;
  }
  if(a.b_get(1,1)==2.1)
  {
    cout<<"b_get success"<<endl;
  }
  else
  {
    cout<<"b_get failure"<<endl;
  }
  if(a.c_get(1,1)==2.1)
  {
    cout<<"c_get success"<<endl;
  }
  else
  {
    cout<<"c_get failure"<<endl;
  }
  if(a.d_get(1,1)==2.1)
  {
    cout<<"d_get success"<<endl;
  }
  else
  {
    cout<<"d_get failure"<<endl;
  }
  if(a.e_get(1,1)==2.1)
  {
    cout<<"e_get success"<<endl;
  }
  else
  {
    cout<<"e_get failure"<<endl;
  }
  if(a.f_get(1,1)==2.1)
  {
    cout<<"f_get success"<<endl;
  }
  else
  {
    cout<<"f_get failure"<<endl;
  }
  if(a.g_get(1,1)==2.1)
  {
    cout<<"g_get success"<<endl;
  }
  else
  {
    cout<<"g_get failure"<<endl;
  }
  if(a.b1_get(1)==0.0)
  {
    cout<<"b1_get success"<<endl;
  }
  else
  {
    cout<<"b1_get failure"<<endl;
  }
  if(a.b2_get(1)==0.0)
  {
    cout<<"b2_get success"<<endl;
  }
  else
  {
    cout<<"b2_get failure"<<endl;
  }
  if(a.b3_get(1)==0.0)
  {
    cout<<"b3_get success"<<endl;
  }
  else
  {
    cout<<"b3_get failure"<<endl;
  }
  if(a.b4_get(1)==0.0)
  {
    cout<<"b4_get success"<<endl;
  }
  else
  {
    cout<<"b4_get failure"<<endl;
  }

}
int main()
{
  test_get();
}
