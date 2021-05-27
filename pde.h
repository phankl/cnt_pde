#ifndef PDE_header
#define PDE_header

#include <vector>
#include <cmath>

#include "math_extra.h"

using namespace std;

class PDE {
  private:
    double dt;
    double dx;

    int nx;
    int nt;

    double c;
    double l;
    double r0;
    double j0;

    double e0;
    double w;

    int step;

    double eps;
    double delta;

    vector<double> previousState;
    vector<double> currentState;
    vector<double> nextState;

    vector<double> implicitEquation(vector<double>&);
    vector<vector<double>> jacobian(vector<double>&);

    vector<double> newtonMethod();

  public:
    PDE();
    PDE(vector<double>&);

    void solve(int);
};

#endif
