#ifndef MATH_EXTRA_header
#define MATH_EXTRA_header

#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

template <typename T> int sgn(T val) {
  return (T(0) < val) - (val < T(0));
}

vector<double> add(vector<double>&, vector<double>&);
vector<double> tridiagonalSystem(vector<vector<double>>&, vector<double>&);

void print(vector<double>&);
void print(vector<vector<double>>&);

#endif
