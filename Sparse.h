#ifndef SPARSE_H
#define SPARSE_H
#include<iostream>
using namespace std;
template<class T, int n>
class Sparse
{
private:
  int *rows;
  int *columns;
  T  *values;
  int matrix_size = n;
  int size_of_sparse = 0;
public:
  Sparse()
  {
      rows  = new int[1]();
      columns  = new int[1]();
      values  = new T[1]();
      cout<<"default constructor called"<<endl;
  }
  Sparse(T given_mat[][n])
  {
    int nonzero = 0;
    for(int i=0; i<n; i++)
    {
      for(int j=0; j<n; j++)
      {
        if(given_mat[i][j] == 0)
        {
          continue;
        }
        else
        {
          nonzero++;
        }
      }
    }
    size_of_sparse = nonzero;
    rows  = new int[nonzero]();
    columns  = new int[nonzero]();
    values  = new T[nonzero]();
    nonzero = 0;
    for(int i=0; i<n; i++)
    {
      for(int j=0; j<n; j++)
      {
        if(given_mat[i][j] == 0)
        {
          continue;
        }
        else
        {
          rows[nonzero] = i;
          columns[nonzero] = j;
          values[nonzero] = given_mat[i][j];
          nonzero++;
        }
      }
    }
  }

  void disp();
  T get_element(int row, int column);
  void add_element(int row, int column, T value);
};

template<class T, int n>
void Sparse<T,n>::disp()
{
  for(int i = 0; i<matrix_size; i++)
  {
    for(int j=0; j<matrix_size; j++)
    {
      cout<< get_element(i,j)<<" ";
    }
    cout<<endl;
  }
}

template<class T, int n>
T Sparse<T,n>::get_element(int row, int column)
{

  for(int i = 0; i<size_of_sparse; i++)
  {
    if(rows[i] == row)
    {
      if(columns[i] == column)
      {
        return values[i];
      }
      else
      {
        continue;
      }
    }
  }
  return 0;
}

template<class T, int n>
void Sparse<T,n>::add_element(int row, int column, T value)
{
  if(value == 0)
  {
    int doNothing = 1;
  }
  else
  {
    size_of_sparse++;
		int *newrow = new int[size_of_sparse]();
    int *newcolumn = new int[size_of_sparse]();
    T *newvalue = new T[size_of_sparse]();
		for(int i = 0;i<size_of_sparse-1;i++)	//old backpack size
		{
			newrow[i] = rows[i];
      newcolumn[i] = columns[i];
      newvalue[i] = values[i];
		}
		newvalue[size_of_sparse-1] = value;
    newrow[size_of_sparse-1] = row;
    newcolumn[size_of_sparse-1] = column;
		delete [] rows;
    delete [] columns;
    // cout<<"before values"<<endl;
    delete [] values;
    // cout<<"after values"<<endl;
		rows = new int[size_of_sparse]();
    columns = new int[size_of_sparse]();			//reset with new size
    values = new T[size_of_sparse]();			//reset with new size

		for(int i = 0;i<size_of_sparse;i++)
		{
			rows[i] = newrow[i];
      columns[i] = newcolumn[i];
      values[i] = newvalue[i];
		}
    delete[] newrow;
    delete[] newcolumn;
    delete[] newvalue;
	}
}
#endif
// int main()
// {
//   int hi[3][3]={{1,2,3},{4,5,6},{7,8,9}};
//   Sparse<double,9> a;
//   a.add_element(0,1,1);
//   a.disp();
//   cout<<"done"<<endl;
//   a.add_element(3,1,2);
//   a.disp();
//   cout<<"done"<<endl;
//   a.add_element(4,2,3);
//   a.disp();
//   cout<<"done"<<endl;
//   a.add_element(3,3,4);
//   a.disp();
//   cout<<"done"<<endl;
//   a.add_element(1,2,3);
//   a.disp();
//   cout<<"done"<<endl;
//   a.add_element(0,2,3);
//
//
//   a.disp();
// }
