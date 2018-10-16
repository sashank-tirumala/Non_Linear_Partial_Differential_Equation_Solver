#include<iostream>
#include<cmath>
#include"Solver.h"

using namespace std;

template<class T, int n>
class LU_DecompositionSolver: public Solver<T,n>
{
private:
  T l_matrix[n][n];
  T u_matrix[n][n];

public:
  LU_DecompositionSolver(T m1[][n], T m2[n]): Solver<T,n>(m1,m2), l_matrix{{}}, u_matrix{{}}
  {
    int n1 = Solver<T,n>::size;
    for (int i = 0; i < n1; i++)
     {

       // Upper Triangular
       for (int k = i; k < n1; k++)
        {

           // Summation of L(i, j) * U(j, k)
           int sum = 0;
           for (int j = 0; j < i; j++)
           {
               sum += (l_matrix[i][j] * u_matrix[j][k]);
           }
           // Evaluating U(i, k)
           u_matrix[i][k] = Solver<T,n>::a_matrix.get_element(i,k) - sum;
         }
         for (int k = i; k < n1; k++)
         {
                if (i == k)
                    l_matrix[i][i] = 1; // Diagonal as 1
                else {

                    // Summation of L(k, j) * U(j, i)
                    int sum = 0;
                    for (int j = 0; j < i; j++)
                        sum += (l_matrix[k][j] * u_matrix[j][i]);

                    // Evaluating L(k, i)
                    l_matrix[k][i] = (Solver<T,n>::a_matrix.get_element(k,i) - sum) / u_matrix[i][i];
                }
            }
     }

   }
   void disp();
   void solve();
};

template<class T, int n>
void LU_DecompositionSolver<T,n>::solve()
{
  int N = Solver<T,n>::size;
  T mat1[n] = {0};
  for(int i=0; i<N; i++)
  {
    mat1[i] = Solver<T,n>::b_matrix[i];
    for(int j=i-1; j>=0; j--)
    {
      mat1[i] -= l_matrix[i][j]*mat1[j];
    }
    mat1[i] = mat1[i]/l_matrix[i][i];
  }
  cout<<"mat1[i] is : "<<endl;
  for(int i=0;i <n; i++)
  {
    cout<<mat1[i]<<endl;
  }
  for (int i = N-1; i >= 0; i--)
  {
      /* start with the RHS of the equation */
      Solver<T,n>::sol_matrix[i] = mat1[i];

      /* Initialize j to i+1 since matrix is upper
         triangular*/
      for (int j=i+1; j<N; j++)
      {
          /* subtract all the lhs values
           * except the coefficient of the variable
           * whose value is being calculated */
          Solver<T,n>::sol_matrix[i] -= u_matrix[i][j]*Solver<T,n>::sol_matrix[j];
      }

      /* divide the RHS by the coefficient of the
         unknown being calculated */
      Solver<T,n>::sol_matrix[i] = Solver<T,n>::sol_matrix[i]/u_matrix[i][i];
  }
  cout<<"\nSolution for the system:\n";
  for (int i=0; i<N; i++)
  {
      cout<<Solver<T,n>::sol_matrix[i]<<endl;
  }
  Solver<T,n>::set_solved();

}
template<class T, int n>
void LU_DecompositionSolver<T,n>::disp()
{
  int n1 = Solver<T,n>::size;
  cout<<"U matrix is: "<<endl;
  for(int i=0;i<n1;i++)
  {
    for(int j=0;j<n1;j++)
    {
      cout<<u_matrix[i][j]<<"\t";
    }
    cout<<endl;
  }
  cout<<"L matrix is: "<<endl;
  for(int i=0;i<n1;i++)
  {
    for(int j=0;j<n1;j++)
    {
      cout<<l_matrix[i][j]<<"\t";
    }
    cout<<endl;
  }
}

// int main()
// {
//     double a[3][3] = {{1,2,3},{4,5,6},{8,8,9}};
//     double v[3] = {11,12,13};
//     LU_DecompositionSolver<double,3> ab(a,v);
//     Solver<double, 3> *i;
//     i = &ab;
//     i->solve();
//     ab.disp();
//
// }
