#ifndef MATH_EXTRA_header
#define MATH_EXTRA_header

#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

vector<double> add(vector<double>&, vector<double>&);
vector<double> tridiagonalSystem(vector<vector<double>>&, vector<double>&);

void print(vector<double>&);
void print(vector<vector<double>>&);

#endif
