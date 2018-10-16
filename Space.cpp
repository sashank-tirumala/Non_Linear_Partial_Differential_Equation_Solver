#include<iostream>
#include<cmath>
#include"PDE.cpp"
#include"Sparse.h"
using namespace std;
 // PDE<T,n>(arr1,arr2,arr3[][n],arr4[][n],arr5[][n],arr6[][n],arr7[][n],arr8[n],arr9[n],arr10[n],arr11[n])
template<class T,class AD_Class, int n>
class Space: public PDE<T,n>
{
  private:
    T space[n][n];
    int size;
    T coeff_matrix[n*n][n*n];


  public:
    Sparse<AD_Class,n*n> jacob_matrix;
    AD_Class constant_matrix[n*n];
    Space(): PDE<T,n>(),space{{}}, size(n), coeff_matrix{{}}, constant_matrix{}
    {
      cout<<"Initialized space"<<endl;
    }
    Space(T arr1[][n], T arr2[][n], T arr3[][n], T arr4[][n], T arr5[][n], T arr6[][n], T arr7[][n], T arr8[n], T arr9[n], T arr10[n], T arr11[n]): PDE<T,n>(arr1,arr2,arr3,arr4,arr5,arr6,arr7,arr8,arr9,arr10,arr11), space{{}}, size(n), coeff_matrix{{}}, constant_matrix{}
    {
      for(int i=0;i<size;i++)
      {
        space[size-i-1][0]=PDE<T,n>::b4_get(i);
        space[0][i]=PDE<T,n>::b1_get(i);
        space[i][size-1]=PDE<T,n>::b2_get(i);
        space[size-1][size - i - 1]=PDE<T,n>::b3_get(i);
      }
      cout<<"Initialized space"<<endl;
    }
    void generate_coeff_and_const_matrix();
    void generate_jacobian_matrix();
    void disp();
    void disp_coeff_matrix();
    void disp_jacob_matrix();
    void disp_constant_matrix();
    void update_space(AD_Class y[n*n]);
    T calc_func_with_der(int pointx,int pointy,int varx,int vary);
    T calc_func_without_der(int pointx, int pointy);
};

template<class T,class AD_Class, int n>
void Space<T,AD_Class,n>::disp()
{
  PDE<T,n>::disp();
  cout<<"Space is: "<<endl;
  for(int i=size-1;i>=0;i--)
  {
    for(int j=0;j<n;j++)
    {
      cout<<space[i][j]<<" ";
    }
    cout<<endl;
  }
}

template<class T,class AD_Class, int n>
void Space<T,AD_Class,n>::disp_jacob_matrix()
{
  cout<<"jacob_matrix is: "<<endl;
  for(int i=0;i<size*size;i++)
  {
    for(int j=0;j<size*size;j++)
    {
      cout<<jacob_matrix.get_element(i,j)<<" ";
    }
    cout<<endl;

  }
}

template<class T,class AD_Class, int n>
void Space<T,AD_Class,n>::disp_coeff_matrix()
{
  cout<<"coeff_matrix is: "<<endl;
  for(int i=0;i<size*size;i++)
  {
    for(int j=0;j<size*size;j++)
    {
      cout<<coeff_matrix[i][j]<<" ";
    }
    cout<<endl;

  }
}

template<class T,class AD_Class, int n>
void Space<T,AD_Class,n>::disp_constant_matrix()
{
  cout<<"constant_matrix is: "<<endl;
  for(int i=0;i<size*size;i++)
  {
    cout<<constant_matrix[i]<<endl;
  }
}

template<class T,class AD_Class, int n>
void Space<T,AD_Class,n>::generate_coeff_and_const_matrix()
{
  AD_Class x_delta = 1/(AD_Class)size;
  AD_Class y_delta = 1/(AD_Class)size;
  int k=0;
  for(int i=0;i<size;i++)
  {
    for(int j=0;j<size;j++)
    {
      if(i==0 || j==0 || i==size-1 || j==size-1)
      {
        coeff_matrix[k][size*i + j] = (AD_Class)1;
      }
      else
      {
        cout<<x_delta<<endl;
        //Finding the adjacent values
        coeff_matrix[k][size*i + j] = (((AD_Class)-2*PDE<T,n>::a_get(i,j))/(x_delta*x_delta)+((AD_Class)-2*PDE<T,n>::b_get(i,j))/(y_delta*y_delta)+PDE<T,n>::f_get(i,j));
        coeff_matrix[k][size*(i+1) + j] = (PDE<T,n>::a_get(i,j))/(x_delta*x_delta)+(PDE<T,n>::d_get(i,j)/((AD_Class)2*x_delta));
        coeff_matrix[k][size*i + (j+1)] = (PDE<T,n>::b_get(i,j))/(y_delta*y_delta)+(PDE<T,n>::e_get(i,j)/((AD_Class)2*y_delta));
        coeff_matrix[k][size*(-1) + j] = (PDE<T,n>::a_get(i,j))/(x_delta*x_delta)+((AD_Class)-1*PDE<T,n>::d_get(i,j)/((AD_Class)2*x_delta));
        coeff_matrix[k][size*i + (j-1)] = (PDE<T,n>::b_get(i,j))/(y_delta*y_delta)+((AD_Class)-1*PDE<T,n>::e_get(i,j)/((AD_Class)2*y_delta));

        //Finding the corner values
        coeff_matrix[k][size*(i+1)+(j+1)]= (PDE<T,n>::c_get(i,j))/((AD_Class)4*x_delta*y_delta);
        coeff_matrix[k][size*(i-1)+(j-1)]= (PDE<T,n>::c_get(i,j))/((AD_Class)4*x_delta*y_delta);
        coeff_matrix[k][size*(i+1)+(j-1)]= ((AD_Class)-1*PDE<T,n>::c_get(i,j))/((AD_Class)4*x_delta*y_delta);
        coeff_matrix[k][size*(i+-1)+(j+1)]= ((AD_Class)-1*PDE<T,n>::c_get(i,j))/((AD_Class)4*x_delta*y_delta);

        //Finding constant matrix values
      }
      k++;
    }
  }
}
template<class T,class AD_Class, int n>
T Space<T,AD_Class,n>::calc_func_with_der(int pointx, int pointy, int varx, int vary)
{
  int start_i = -1;
  int start_j = -1;
  AD_Class x_delta = 1/(AD_Class)size;
  AD_Class y_delta = 1/(AD_Class)size;
  T A_current,B_current,C_current,D_current,E_current,F_current,G_current;
  T u[3][3]={{}};
  if(pointx == varx && pointy == vary)
  {
    A_current = PDE<T,n>::a_get(pointx,pointy);
    B_current = PDE<T,n>::b_get(pointx,pointy);
    C_current = PDE<T,n>::c_get(pointx,pointy);
    D_current = PDE<T,n>::d_get(pointx,pointy);
    E_current = PDE<T,n>::e_get(pointx,pointy);
    F_current = PDE<T,n>::f_get(pointx,pointy);
    G_current = PDE<T,n>::g_get(pointx,pointy);
  }
  else
  {
    A_current = PDE<T,n>::a_get(pointx,pointy).ADconst();
    B_current = PDE<T,n>::b_get(pointx,pointy).ADconst();
    C_current = PDE<T,n>::c_get(pointx,pointy).ADconst();
    D_current = PDE<T,n>::d_get(pointx,pointy).ADconst();
    E_current = PDE<T,n>::e_get(pointx,pointy).ADconst();
    F_current = PDE<T,n>::f_get(pointx,pointy).ADconst();
    G_current = PDE<T,n>::g_get(pointx,pointy).ADconst();

  }
  for(int start_i = -1; start_i < 2; start_i++)
  {
    for(int start_j = -1; start_j < 2; start_j++)
    {
      int current_x = pointx + start_i;
      int current_y = pointy + start_j;
      if(current_x == varx && current_y == vary)
      {
          u[start_i+1][start_j+1] = space[varx][vary];
      }
      else
      {
          u[start_i+1][start_j+1] = space[current_x][current_y].ADconst();
      }
    }
  }
  T res;
  res = A_current*(u[1][2]+u[1][0]-(AD_Class)2*u[1][1])/(x_delta*x_delta);
  res = res + B_current*(u[0][1]+u[2][1]-(AD_Class)2*u[1][1])/(x_delta*x_delta);
  res = res + C_current*(u[2][2]+u[0][0]-u[2][0]-u[0][2])/((AD_Class)4*x_delta*y_delta);
  res = res + D_current*(u[1][2]-u[1][0])/(x_delta*(AD_Class)2);
  res = res + E_current*(u[2][1]-u[0][1])/(y_delta*(AD_Class)2);
  res = res + F_current*u[1][1];
  return res;
}
template<class T,class AD_Class, int n>
T Space<T,AD_Class,n>::calc_func_without_der(int pointx, int pointy)
{
  int start_i = -1;
  int start_j = -1;
  AD_Class x_delta = 1/(AD_Class)size;
  AD_Class y_delta = 1/(AD_Class)size;
  T A_current,B_current,C_current,D_current,E_current,F_current,G_current;
  T u[3][3]={{}};
  A_current = PDE<T,n>::a_get(pointx,pointy);
  B_current = PDE<T,n>::b_get(pointx,pointy);
  C_current = PDE<T,n>::c_get(pointx,pointy);
  D_current = PDE<T,n>::d_get(pointx,pointy);
  E_current = PDE<T,n>::e_get(pointx,pointy);
  F_current = PDE<T,n>::f_get(pointx,pointy);
  G_current = PDE<T,n>::g_get(pointx,pointy);
  for(int start_i = -1; start_i < 2; start_i++)
  {
    for(int start_j = -1; start_j < 2; start_j++)
    {
      int current_x = pointx + start_i;
      int current_y = pointy + start_j;
      u[start_i+1][start_j+1] = space[current_x][current_y];
    }
  }
  T res;
  res = A_current*(u[1][2]+u[1][0]-(AD_Class)2*u[1][1])/(x_delta*x_delta);
  res = res + B_current*(u[0][1]+u[2][1]-(AD_Class)2*u[1][1])/(y_delta*y_delta);
  res = res + C_current*(u[2][2]+u[0][0]-u[2][0]-u[0][2])/((AD_Class)4*x_delta*y_delta);
  res = res + D_current*(u[1][2]-u[1][0])/(x_delta*(AD_Class)2);
  res = res + E_current*(u[2][1]-u[0][1])/(y_delta*(AD_Class)2);
  res = res + F_current*u[1][1];
  res = res + G_current;
  return res;
}
template<class T,class AD_Class, int n>
void Space<T,AD_Class,n>::generate_jacobian_matrix()
{
  int k=0;
  jacob_matrix.disp();
  for(int i=0;i<n;i++)
  {
    for(int j =0;j<n;j++)
    {
      if(i==0 || j==0 || i==size-1 || j==size-1)
      {
        // jacob_matrix.add_element(0,1,1);
        jacob_matrix.add_element(k,size*i+j,(AD_Class)1);
        constant_matrix[k] = space[i][j].f;
      }
      else
      {
        constant_matrix[k] = calc_func_without_der(i,j).f;
        jacob_matrix.add_element(k,size*i+j,calc_func_with_der(i,j,i,j).fd);
        jacob_matrix.add_element(k,size*i+j-1,calc_func_with_der(i,j,i,j-1).fd);
        jacob_matrix.add_element(k,size*i+j+1,calc_func_with_der(i,j,i,j+1).fd);
        jacob_matrix.add_element(k,size*(i+1)+j,calc_func_with_der(i,j,i+1,j).fd);
        jacob_matrix.add_element(k,size*(i-1)+j,calc_func_with_der(i,j,i-1,j).fd);
        jacob_matrix.add_element(k,size*(i+1)+j+1,calc_func_with_der(i,j,i+1,j+1).fd);
        jacob_matrix.add_element(k,size*(i-1)+j-1,calc_func_with_der(i,j,i-1,j-1).fd);
        jacob_matrix.add_element(k,size*(i+1)+j-1,calc_func_with_der(i,j,i+1,j-1).fd);
        jacob_matrix.add_element(k,size*(i-1)+j+1,calc_func_with_der(i,j,i-1,j+1).fd);
      }
      k++;
    }
  }
}
template<class T,class AD_Class,int n>
void Space<T,AD_Class, n>::update_space(AD_Class y[n*n])
{
  for(int i =0; i<n; i++)
  {
    for(int j=0; j<n; j++)
    {
      space[i][j] = space[i][j] + y[size*i + j];
    }
  }
}
// 
// int main()
// {
//     // float r = 8;
//     // cout<<r<<endl;
//     // AD<double> a1(1.1,1.1,1.1);
//     // AD<double> b1(1.1,1.1,1.1);
//     // AD<double> c1(0.0,0.0,0.0);
//     // AD<double> arr1[3][3]={{a1, a1, a1},{a1, a1, a1},{a1, a1, a1}};
//     // AD<double> arr2[3][3]={{c1, c1, c1},{c1, c1, c1},{c1, c1, c1}};
//     // AD<double> b11[3] = {a1,b1,a1};
//     // Space<AD<double>,double, 3> a(arr1, arr1, arr2, arr2, arr2, arr2, arr2, b11, b11, b11, b11);
//     // a.generate_jacobian_matrix();
//     // a.disp_jacob_matrix();
//     // a.disp_constant_matrix();
//     //
//     // a.disp();
//     // a.disp();
//     // a.generate_coeff_and_const_matrix();
//     // a.disp_coeff_matrix();
//     // a.disp_constant_matrix();
//     double sol[9]= {1,2,3,4,5,6,7,8,9};
//     Space<AD<double>,double,3> a;
//     a.update_space(sol);
//     a.disp();
//
// }
