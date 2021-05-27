#include "math_extra.h"

using namespace std;

vector<double> add(vector<double>& a, vector<double>& b) {

  int n = a.size();
  vector<double> c = vector<double>(n, 0);
  
  for (int i = 0; i < n; i++) c[i] = a[i] + b[i];

  return c;
}

vector<double> tridiagonalSystem(vector<vector<double>>& a, vector<double>& b) {
  
  /*
    solves a tridiagonal linear system using 
    gaussian elimination with partial pivoting
    
    a: tridiagonal square matrix
    b: rhs vector

    returns solution of system x
  */

  int n = a.size();

  // pivot and gaussian elimination

  for (int i = 0; i < n-1; i++) {

    // pivot, swap rows if necessary

    if (fabs(a[i+1][i]) > fabs(a[i][i])) {
      swap(a[i], a[i+1]);
      swap(b[i], b[i+1]);

      // gaussian elimination
      
      double ratio = a[i+1][i] / a[i][i];

      a[i+1][i] = 0.0;
      a[i+1][i+1] -= ratio * a[i][i+1];
      a[i+1][i+2] -= ratio * a[i][i+2];
      
      b[i+1] -= ratio * b[i];
    } 
    else {

      // gaussian elimination, fewer elements

      double ratio = a[i+1][i] / a[i][i];

      a[i+1][i] = 0.0;
      a[i+1][i+1] -= ratio * a[i][i+1];

      b[i+1] -= ratio * b[i];
    }
  }
  
  print(a);
  print(b);

  // back substitution

  vector<double> c = vector<double>(n, 0);

  // last two entries

  c[n-1] = b[n-1] / a[n-1][n-1];
  c[n-2] = (b[n-2] - a[n-2][n-1]*c[n-1]) / a[n-2][n-2];

  // all other entries
  
  for (int i = n-3; i > -1; i--)
    c[i] = (b[i] - a[i][i+1]*c[i+1] - a[i][i+2]*c[i+2]) / a[i][i];

  return c;
}

void print(vector<double>& a) {
  int n = a.size();
  
  cout << "( ";
  for (int i = 0; i < n; i++) cout << a[i] << " ";
  cout << ")" << endl << endl;
}

void print(vector<vector<double>>& a) {
  int m = a.size();
  int n = a[0].size();

  for (int i = 0; i < m; i++) {
    cout << "( ";
    for (int j = 0; j < n; j++) cout << a[i][j] << " ";
    cout << ")" << endl;
  }
  cout << endl;
}
