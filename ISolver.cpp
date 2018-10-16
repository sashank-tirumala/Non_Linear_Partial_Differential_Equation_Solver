#include<iostream>
#include<cmath>
#include"Solver.h"

using namespace std;

template<class T, int n>
class ISolver: public Solver<T,n>
{
protected:
  T y[n];
  double error_tolerance;
public:
  ISolver(Sparse<T,n> m1, T m2[n]): Solver<T,n>(m1,m2), y{}, error_tolerance(0.01){}
  void update_solver();
  int check_error();
};

template<class T, int n>
int ISolver<T,n>::check_error()
{
  for(int i=0; i<n; i++)
  {
    if(abs(Solver<T,n>::sol_matrix[i] - y[i]) < error_tolerance){}
    else
    {
      return 1;
    }
  }
  return 0;
}

template<class T, int n>
void ISolver<T,n>::update_solver()
{
  for(int i=0; i<n; i++)
  {
    Solver<T,n>::sol_matrix[i] = y[i];
  }
}

//
// template<class T, int n>
// void ISolver<T,n>::solve()
// {
//   double current[n] = {};
//   bool error = 1;
//   int k=0;
//   while (error)
//     {
//         for (int i = 0; i < n; i++)
//         {
//             y[i] = (Solver<T,n>::b_matrix[i] / Solver<T,n>::a_matrix[i][i]);
//             for (int j = 0; j < n; j++)
//             {
//                 if (j == i)
//                     continue;
//                 y[i] = y[i] - ((Solver<T,n>::a_matrix[i][j] / Solver<T,n>::a_matrix[i][i]) * Solver<T,n>::sol_matrix[j]);
//             }
//         }
//         error = check_error();
//         update_solver();
//         k++;
//         cout<<"Iter"<<k<<" completed"<<endl;
//     }
// }
//
// int main()
// {
//     double a[3][3] = {{4,1,-1},{2,7,1},{1,-3,12}};
//     double v[3] = {3,19,31};
//     ISolver<double,3> ab(a,v);
//     Solver<double, 3> *i;
//     i = &ab;
//     // i->disp();
//     i->solve();
//     i->disp();
// }
