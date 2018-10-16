#include<iostream>
#include "AD.h"
using namespace std;
template<class T, int n>
class PDE
{
  private:
    T a_coeff[n][n], b_coeff[n][n], c_coeff[n][n], d_coeff[n][n], e_coeff[n][n], f_coeff[n][n], g_coeff[n][n];
    T b1_coeff[n], b2_coeff[n], b3_coeff[n], b4_coeff[n];
  public:
    PDE() : a_coeff{{}}, b_coeff{{}}, c_coeff{{}}, d_coeff{{}}, e_coeff{{}}, f_coeff{{}}, g_coeff{{}}, b1_coeff{}, b2_coeff{}, b3_coeff{}, b4_coeff{}
    {
      ;
    }
    PDE(T arr1[][n], T arr2[][n], T arr3[][n], T arr4[][n], T arr5[][n], T arr6[][n], T arr7[][n], T arr8[n], T arr9[n], T arr10[n], T arr11[n]): a_coeff{}, b_coeff{}, c_coeff{}, d_coeff{}, e_coeff{}, f_coeff{}, g_coeff{}, b1_coeff{}, b2_coeff{}, b3_coeff{}, b4_coeff{}
    {

      for (int i = 0; i< n ; i++)
      {
        for(int j=0; j<n; j++)
        {
          a_coeff[i][j]=arr1[i][j];
          b_coeff[i][j]=arr2[i][j];
          c_coeff[i][j]=arr3[i][j];
          d_coeff[i][j]=arr4[i][j];
          e_coeff[i][j]=arr5[i][j];
          f_coeff[i][j]=arr6[i][j];
          g_coeff[i][j]=arr7[i][j];
        }
        b1_coeff[i]=arr8[i];
        b2_coeff[i]=arr9[i];
        b3_coeff[i]=arr10[i];
        b4_coeff[i]=arr11[i];
      }

    }
    void disp();
    T a_get(int,int);
    T b_get(int,int);
    T c_get(int,int);
    T d_get(int,int);
    T e_get(int,int);
    T f_get(int,int);
    T g_get(int,int);
    T b1_get(int);
    T b2_get(int);
    T b3_get(int);
    T b4_get(int);



};

// ALL GET CLASS METHODS //
template<class T, int n>
T PDE<T,n>::a_get(int n1,int n2)
{
  return a_coeff[n1][n2];
}
template<class T, int n>
T PDE<T,n>::b_get(int n1,int n2)
{
  return b_coeff[n1][n2];
}
template<class T, int n>
T PDE<T,n>::c_get(int n1,int n2)
{
  return c_coeff[n1][n2];
}
template<class T, int n>
T PDE<T,n>::d_get(int n1,int n2)
{
  return d_coeff[n1][n2];
}
template<class T, int n>
T PDE<T,n>::e_get(int n1,int n2)
{
  return e_coeff[n1][n2];
}
template<class T, int n>
T PDE<T,n>::f_get(int n1,int n2)
{
  return f_coeff[n1][n2];
}
template<class T, int n>
T PDE<T,n>::g_get(int n1,int n2)
{
  return g_coeff[n1][n2];
}
template<class T, int n>
T PDE<T,n>::b1_get(int n1)
{
  return b1_coeff[n1];
}
template<class T, int n>
T PDE<T,n>::b2_get(int n1)
{
  return b2_coeff[n1];
}
template<class T, int n>
T PDE<T,n>::b3_get(int n1)
{
  return b3_coeff[n1];
}
template<class T, int n>
T PDE<T,n>::b4_get(int n1)
{
  return b4_coeff[n1];
}



template<class T, int n>
void PDE<T,n>::disp()
{
  cout<<"A is: "<<endl;
  for (int i = 0; i< n ; i++)
  {
    for(int j =0; j <n; j ++)
    {
      cout << a_coeff[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
  cout<<"B is: "<<endl;
  for (int i = 0; i< n ; i++)
  {
    for(int j =0; j <n; j ++)
    {
      cout << b_coeff[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
  cout<<"C is: "<<endl;
  for (int i = 0; i< n ; i++)
  {
    for(int j =0; j <n; j ++)
    {
      cout << c_coeff[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
  cout<<"D is: "<<endl;
  for (int i = 0; i< n ; i++)
  {
    for(int j =0; j <n; j ++)
    {
      cout << d_coeff[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
  cout<<"E is: "<<endl;
  for (int i = 0; i< n ; i++)
  {
    for(int j =0; j <n; j ++)
    {
      cout << e_coeff[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
  cout<<"F is: "<<endl;
  for (int i = 0; i< n ; i++)
  {
    for(int j =0; j <n; j ++)
    {
      cout << f_coeff[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
  cout<<"G is: "<<endl;
  for (int i = 0; i< n ; i++)
  {
    for(int j =0; j <n; j ++)
    {
      cout << g_coeff[i][j]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
  cout<<"Boundary conditions of the PDE is: "<<endl;
  cout<<"B1 is: "<<endl;
  for (int i = 0; i< n ; i++)
  {
    cout << b1_coeff[i]<<" ";
  }
  cout<<endl;
  cout<<"B2 is: "<<endl;
  for (int i = 0; i< n ; i++)
  {
    cout << b2_coeff[i]<<" ";
  }
  cout<<endl;
  cout<<"B3 is: "<<endl;
  for (int i = 0; i< n ; i++)
  {
    cout << b3_coeff[i]<<" ";
  }
  cout<<endl;
  cout<<"B4 is: "<<endl;
  for (int i = 0; i< n ; i++)
  {
    cout << b4_coeff[i]<<" ";
  }
  cout<<endl;

}
// int main()
// {
//   // double arr1[3][3]={{1.1, 2.1, 3.1},{1.1, 2.1, 3.1},{1.1, 2.1, 3.1}};
//   // double arr2[3]={1.0, 0.0, 1.0};
//   // PDE<double, 3> a(arr1, arr1, arr1, arr1, arr1, arr1, arr1, arr2, arr2, arr2, arr2);
//   PDE<AD<double>,3> a;
//   a.disp();
// }
