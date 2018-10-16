#ifndef SOLVER_H
#define SOLVER_H
#include<iostream>
#include<cmath>
#include"Sparse.h"
using namespace std;
template<class T, int n>
class Solver
{
private:
  bool solved;
protected:
  Sparse<T,n> a_matrix;
  T b_matrix[n];
  int size;
public:
  T sol_matrix[n];
  Solver(Sparse<T,n> m1, T m2[n]): sol_matrix{}, size(n), solved(0)
  {
    for(int i=0;i<n;i++)
    {
      b_matrix[i] = m2[i];
    }
    a_matrix = m1;
    a_matrix.disp();
  }
  virtual void solve();
  virtual void disp();
  void set_solved();
  int get_solved();
};


template<class T, int n>
void Solver<T,n>::solve()
{
  cout<<"parent function solve called: "<<endl;
}

template<class T, int n>
void Solver<T,n>::disp()
{

  cout<<"Ax = B where A is:"<<endl;
  for(int i=0; i <n; i ++)
  {
    for(int j=0; j<n; j++)
    {
      cout<<a_matrix.get_element(i,j)<<"\t";
    }
    cout<<endl;
  }
  cout<<"B is: "<<endl;
  for(int i =0; i<n; i++)
  {
    cout<<b_matrix[i]<<endl;
  }
  cout<<"Soln is:"<<endl;
  for(int i =0; i<n; i++)
  {
    cout<<sol_matrix[i]<<endl;
  }

}

template<class T, int n>
void Solver<T,n>::set_solved()
{
  solved = 1;
}

template<class T, int n>
int Solver<T,n>::get_solved()
{
  return solved;
}
#endif
// int main()
// {
//   int a[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
//   Sparse<int,3> b(a);
//   int v[3] = {11,12,13};
//   Solver<int,3> ab(b,v);
//   ab.disp();
// }
