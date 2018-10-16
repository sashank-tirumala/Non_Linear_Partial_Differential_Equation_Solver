#include<iostream>
#include<cmath>
#include"Solver.h"

using namespace std;

template<class T, int n>
class TriDiagonalSolver: public Solver<T,n>
{
protected:
  T a[n],b[n],c[n],d[n];
public:
  TriDiagonalSolver(Sparse<T,n> m1, T m2[n]): Solver<T,n>(m1,m2), a{}, b{}, c{}, d{}
  {
    for(int i =0; i<n ;i++)
    {
      for(int j = 0; j<n ; j++)
      {
        if(j == i)
        {
          b[i] = Solver<T,n>::a_matrix.get_element(i,i);
        }
        if(j == i-1)
        {
          a[i] = Solver<T,n>::a_matrix.get_element(i,i);
        }
        if(j == i+1)
        {
          c[i] = Solver<T,n>::a_matrix.get_element(i,j);
        }
      }
      d[i] = Solver<T,n>::b_matrix[i];
    }
  }
  void solve();
  void disp();

};

template<class T, int n>
void TriDiagonalSolver<T,n>::solve()
{
  for(int i=0; i<n; i++)
  {
    if(i ==0)
    {
      c[i] = c[i]/b[i];
      d[i] = d[i]/b[i];
    }
    else
    {
      c[i] = c[i]/(b[i] - a[i]*c[i-1]);
      d[i] = (d[i]-a[i]*d[i-1])/(b[i]-a[i]*c[i-1]);
    }
  }
  for(int i = n-1; i>=0; i--)
  {
    if(i == n-1)
    {
      Solver<T,n>::sol_matrix[i] = d[i];
    }
    else
    {
      Solver<T,n>::sol_matrix[i] = d[i] - c[i]*Solver<T,n>::sol_matrix[i+1];
    }

  }
  Solver<T,n>::set_solved();
}

template<class T, int n>
void TriDiagonalSolver<T,n>::disp()
{
  if(Solver<T,n>::get_solved())
  {
    Solver<T,n>::disp();
  }
  else
  {
    cout<<"A is: "<<endl;
    for(int i=0; i<n; i++)
    {
      cout<<a[i]<<"\t";
    }
    cout<<endl;
    cout<<"B is: "<<endl;
    for(int i=0; i<n; i++)
    {
      cout<<b[i]<<"\t";
    }
    cout<<endl;
    cout<<"C is: "<<endl;
    for(int i=0; i<n; i++)
    {
      cout<<c[i]<<"\t";
    }
    cout<<endl;
    cout<<"D is: "<<endl;
    for(int i=0; i<n; i++)
    {
      cout<<d[i]<<"\t";
    }
    cout<<endl;
  }
}

// int main()
// {
//     double a[4][4] = {{2,3,0,0},{6,3,9,0},{0,2,5,2},{0,0,4,3}};
//     double v[4] = {21,69,34,22};
//     Sparse<double,4> b(a);
//     TriDiagonalSolver<double,4> ab(b,v);
//     Solver<double, 4> *i;
//     i = &ab;
//     // i->disp();
//     i->solve();
//     i->disp();
// }
