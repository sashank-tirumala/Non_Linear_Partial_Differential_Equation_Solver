#include<iostream>
#include"Space.cpp"
#include"GaussEliminationSolver.cpp"
#include"GaussJacobiSolver.cpp"
#include"GaussSiedelSolver.cpp"
#include"ISolver.h"
#include"TriDiagonalSolver.cpp"
#include"SORSolver.cpp"
#include"LU_DecompositionSolver.cpp"

using namespace std;
template<class T, class AD_Class, int n>
class FinalController
{
private:
  Space<T,AD_Class,n> current_space;
  GaussEliminationSolver<AD_Class, n*n> gauss_elim_solver;
  GaussJacobiSolver<AD_Class, n*n> gauss_jacobi_solver;
  LU_DecompositionSolver<AD_Class, n*n> lu_decomposition_solver;
  TriDiagonalSolver<AD_Class, n*n> tri_diagonal_solver;
  SORSolver<AD_Class, n*n> sor_solver;
  GaussSiedelSolver<AD_Class, n*n> gauss_siedel_solver;
  Solver<AD_Class, n*n> linear_solver;
  int chooser;

public:
  FinalController(Space<T,AD_Class,n> space): current_space(space)
  {
    ;
  }
  void solve_one_step();
};

template<class T, class AD_Class, int n>
void FinalController<T,AD_Class,n>::solve_one_step()
{
  current_space.generate_jacobian_matrix();
  GaussEliminationSolver<AD_Class, n*n> gauss_elim_solver(current_space.jacob_matrix, current_space.constant_matrix);

}



int main()
{
  AD<double> x1(0,1,0);
  AD<double> x2(0.33,1,0);
  AD<double> x3(0.66,1,0);
  AD<double> x4(0.99,1,0);
  AD<double> b1(0,0,0);
  AD<double> b2(0.5,1,0);
  AD<double> bdry[4] = {b1,b2,b2,b1};
  AD<double> A[4][4] ={{x1,x2,x3,x4},{x1,x2,x3,x4},{x1,x2,x3,x4},{x1,x2,x3,x4}};
  AD<double> zr[4][4]={{b1,b1,b1,b1},{b1,b1,b1,b1},{b1,b1,b1,b1},{b1,b1,b1,b1}};
  Space<AD<double>,double,4> current_space(A,A,zr,zr,zr,zr,zr,bdry,bdry,bdry,bdry);
  current_space.generate_jacobian_matrix();
  GaussEliminationSolver<double,16>soln(current_space.jacob_matrix, current_space.constant_matrix);
  Solver<double, 16> *i;
  i = &soln;
  i->solve();
  i->disp();
  current_space.update_space(i->sol_matrix);
  current_space.disp();
}
