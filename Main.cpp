#include<iostream>
#include"Space.h"
#include"Solver.h"
#include"GaussEliminationSolver.h"
#include"GaussJacobiSolver.h"
#include"GaussSiedelSolver.h"
#include"ISolver.h"
#include"TriDiagonalSolver.h"
#include"SORSolver.h"
#include"LU_DecompositionSolver.h"

using namespace std;


template<class AD_Class,int n>
float calc_error(AD_Class soln[n], AD_Class prev_soln[n*n])
{
  double sum;
  for(int i = 0; i< n; i++)
  {
    double diff = soln[i] - prev_soln[i];
    sum = sum + diff*diff;
  }
  sum = sqrt(sum);
  return sum;
}

template<class T,class AD_Class, int n>
void newton_raphson_method(Space<T,AD_Class,n> space, Solver<AD_Class, n*n> *solvy)
{
  float error = 1000;
  AD_Class prev_soln[n*n] = {};
  while(error > 0.25)
  {
    space.generate_jacobian_matrix();
    // GaussJacobiSolver<AD_Class,n*n> gjs(space.jacob_matrix,space.constant_matrix);
    solvy->generate_matrix(space.jacob_matrix, space.constant_matrix);
    // gjs.solve();
    solvy->solve();
    space.update_space(solvy->sol_matrix);
    // space.update_space(gjs.sol_matrix);
    // error = calc_error<AD_Class,n*n>(gjs.sol_matrix, prev_soln);
    error = calc_error<AD_Class,n*n>(solvy->sol_matrix, prev_soln);
    cout<<"soln is: "<<endl;
    for(int i =0; i < n*n ; i++)
    {
      // prev_soln[i] = gjs.sol_matrix[i];
      prev_soln[i] = solvy->sol_matrix[i];
      cout<<prev_soln[i]<<" ";
    }
    cout<<endl;
    cout<<"error: "<<error<<endl;

  }
}


int main()
{
  // Below are USER INPUTS

  /*Size is size of the space between 0,1. Size 1000 is space divided into 1000* 1000 points */
  const int size  = 3;
  /* Change below integer, to choose the type of solver:
     0 - Gauss Elimination Solver
     1 - Gauss Jacobi Solver
     2 - Gauss Siedel Solver
     3 - LU Decomposition Solver
     4 - Successive Over Relaxation Solver
     5 - Tri - diagonal Solver
  */
  int solver_type = 1;

  /* END */

  Solver<double,size*size> * solvers[6];
  GaussEliminationSolver<double,size*size> ges;
  GaussJacobiSolver<double,size*size> gjs;
  GaussSiedelSolver<double,size*size> gss;
  LU_DecompositionSolver<double,size*size> lus;
  SORSolver<double,size*size> sors;
  TriDiagonalSolver<double,size*size> tds;
  solvers[0] = &ges;
  solvers[1] = &gjs;
  solvers[2] = &gss;
  solvers[3] = &lus;
  solvers[4] = &sors;
  solvers[5] = &tds;

  /* Change below values to change the input coefficients of the PDE */
  AD<double> a1(1.1,1.1,1.1);
  AD<double> b1(1.1,1.1,1.1);
  AD<double> c1(0.0,0.0,0.0);
  AD<double> arr1[size][size]={{a1, a1, a1},{a1, a1, a1},{a1, a1, a1}};
  AD<double> arr2[size][size]={{c1, c1, c1},{c1, c1, c1},{c1, c1, c1}};
  AD<double> b11[size] = {a1,b1,a1};
  Space<AD<double>,double, size> a(arr1, arr1, arr2, arr2, arr2, arr2, arr2, b11, b11, b11, b11);
  /* Input END */

  newton_raphson_method(a, solvers[solver_type]);
  a.disp();
  return 0;
}
