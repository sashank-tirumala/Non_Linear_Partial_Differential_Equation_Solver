#include<iostream>
#include"ISolver.h"
using namespace std;

template<class T, int n>
class SORSolver: public ISolver<T,n>
{
private:
  double omega;
public:
  SORSolver(Sparse<T,n> m1, T m2[n], double relaxation_factor): ISolver<T,n>(m1, m2), omega(relaxation_factor){;}
  void solve();
};

template<class T, int n>
void SORSolver<T,n>::solve()
{
  bool error = 1;
  int k=0;
  while (error)
    {
        for (int i = 0; i < n; i++)
        {
            ISolver<T,n>::y[i] = (1-omega)*Solver<T,n>::sol_matrix[i] + omega*(Solver<T,n>::b_matrix[i] / Solver<T,n>::a_matrix.get_element(i,i));
            for (int j = 0; j < n; j++)
            {
                if (j == i)
                    continue;
                if(j>i)
                {
                  ISolver<T,n>::y[i] = ISolver<T,n>::y[i] - omega*((Solver<T,n>::a_matrix.get_element(i,j) / Solver<T,n>::a_matrix.get_element(i,i)) * Solver<T,n>::sol_matrix[j]);
                }
                if(j<i)
                {
                  ISolver<T,n>::y[i] = ISolver<T,n>::y[i] - omega*((Solver<T,n>::a_matrix.get_element(i,j) / Solver<T,n>::a_matrix.get_element(i,i)) * ISolver<T,n>::y[j]);
                }
            }
        }
        error = ISolver<T,n>::check_error();
        ISolver<T,n>::update_solver();
        k++;
        if(k > 20)
        {
          cout<<"have crossed 20 iterations, either it does not converge or your conditions are too strict. Proceeding to abort"<<endl;
          break;
        }
        cout<<"Iter"<<k<<" completed"<<endl;
    }
    Solver<T,n>::set_solved();
}
// int main()
// {
//     double a[3][3] = {{4,1,-1},{2,7,1},{1,-3,12}};
//     double v[3] = {3,19,31};
//     Sparse<double,3> b(a);
//     SORSolver<double,3> ab(b,v,0.5);
//     Solver<double, 3> *i;
//     i = &ab;
//     // i->disp();
//     i->solve();
//     i->disp();
// }
