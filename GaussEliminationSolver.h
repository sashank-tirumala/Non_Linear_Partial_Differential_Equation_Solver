#ifndef GAUSSELIMINATIONSOLVER_H
#define GAUSSELIMINATIONSOLVER_H
#include<iostream>
#include<cmath>

#include"Solver.h"


template<class T, int n>
class GaussEliminationSolver: public Solver<T,n>
{
private:
  T aug_mat[n][n+1];
  public:
    GaussEliminationSolver():Solver<T,n>(){};
    GaussEliminationSolver(Sparse<T,n> m1, T m2[n]): Solver<T,n>(m1,m2)
    {
      for(int i=0;i<n;i++)
      {
        for(int j=0;j<n+1;j++)
        {
          if(j == n)
          {
            aug_mat[i][j] = Solver<T,n>::b_matrix[i];
          }
          else
          {
            aug_mat[i][j] = Solver<T,n>::a_matrix.get_element(i,j);
          }
        }
      }
    }
    void solve();
    void swap_row(int i, int j);
    void disp();
    int forwardElim();
    void backSub();
};

template<class T, int n>
void GaussEliminationSolver<T,n>::solve()
{
  cout<<"Guass Elimination Solver function called: "<<endl;
  /* reduction into r.e.f. */
  int N = Solver<T,n>::size;
  int singular_flag = forwardElim();

  /* if matrix is singular */
  if (singular_flag != -1)
  {
      cout<<"Singular Matrix"<<endl;

      /* if the RHS of equation corresponding to
         zero row  is 0, * system has infinitely
         many solutions, else inconsistent*/
      if (aug_mat[singular_flag][N])
          cout<<"Inconsistent System."<<endl;
      else
          cout<<"May have infinitely many solutions"<<endl;
      return;
  }
  /* get solution to system and print it using
     backward substitution */
  backSub();
  Solver<T,n>::set_solved();
}

template<class T, int n>
void GaussEliminationSolver<T,n>::disp()
{
  cout<<"Augmented matrix is: "<<endl;
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n+1;j++)
    {
      cout<<aug_mat[i][j]<<"\t";
    }
    cout<<endl;
  }

}

template<class T, int n>
void GaussEliminationSolver<T,n>::swap_row(int i, int j)
{
    for (int k=0; k< Solver<T,n>::size + 1; k++)
    {
        T temp = aug_mat[i][k];
        aug_mat[i][k]= aug_mat[j][k];
        aug_mat[j][k] = temp;
    }
    cout<<"Guass Swap Solver function called: "<<endl;
    // this->disp();
}

template<class T, int n>
int GaussEliminationSolver<T,n>::forwardElim()
{
    int N = Solver<T,n>::size;
    for (int k=0; k<N; k++)
    {
        // Initialize maximum value and index for pivot
        int i_max = k;
        int v_max = aug_mat[i_max][k];

        /* find greater amplitude for pivot if any */
        for (int i = k+1; i < N; i++)
            if (abs(aug_mat[i][k]) > v_max)
                v_max = aug_mat[i][k], i_max = i;

        /* if a prinicipal diagonal element  is zero,
         * it denotes that matrix is singular, and
         * will lead to a division-by-zero later. */
        if (!aug_mat[k][i_max])
            return k; // Matrix is singular

        /* Swap the greatest value row with current row */
        if (i_max != k)
            swap_row(k, i_max);


        for (int i=k+1; i<N; i++)
        {
            /* factor f to set current row kth elemnt to 0,
             * and subsequently remaining kth column to 0 */
            double f = aug_mat[i][k]/aug_mat[k][k];

            /* subtract fth multiple of corresponding kth
               row element*/
            for (int j=k+1; j<=N; j++)
                aug_mat[i][j] -= aug_mat[k][j]*f;

            /* filling lower triangular matrix with zeros*/
            aug_mat[i][k] = 0;
        }

        // this->disp();        //for matrix state
    }
    // this->disp();           //for matrix state
    return -1;
}

template<class T, int n>
void GaussEliminationSolver<T,n>::backSub()
{
    /* Start calculating from last equation up to the
       first */
    int N = Solver<T,n>::size;
    for (int i = N-1; i >= 0; i--)
    {
        /* start with the RHS of the equation */
        Solver<T,n>::sol_matrix[i] = aug_mat[i][N];

        /* Initialize j to i+1 since matrix is upper
           triangular*/
        for (int j=i+1; j<N; j++)
        {
            /* subtract all the lhs values
             * except the coefficient of the variable
             * whose value is being calculated */
            Solver<T,n>::sol_matrix[i] -= aug_mat[i][j]*Solver<T,n>::sol_matrix[j];
        }

        /* divide the RHS by the coefficient of the
           unknown being calculated */
        Solver<T,n>::sol_matrix[i] = Solver<T,n>::sol_matrix[i]/aug_mat[i][i];
    }

    cout<<"\nSolution for the system:\n";
    for (int i=0; i<N; i++)
    {
        cout<<Solver<T,n>::sol_matrix[i]<<endl;
    }
}
#endif
