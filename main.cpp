#include <vector>

#include "math_extra.h"

using namespace std;

int main() {

  vector<vector<double>> a = {
    {1, 2, 0, 0},
    {3, 4, 5, 0},
    {0, 6, 7, 8},
    {0, 0, 9, 10}
  };

  vector<double> b = {1, 1, 1, 1};

  print(a);
  print(b);

  vector<double> c = tridiagonalSystem(a, b);

  print(c);

  return 0;
}
