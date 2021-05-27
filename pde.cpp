#include "pde.h"

using namespace std;

PDE::PDE() {
  dt = 0.0;
  dx = 0.0;

  nx = 1;
  nt = 1;

  c = 0.0;
  l = 0.0;
  r0 = 0.0;
  j0 = 0.0;

  e0 = 0.0;
  w = 0.0;

  step = 0;

  previousState = vector<double>(nx, 0.0);
  currentState = vector<double>(nx, 0.0);
}

PDE::PDE(vector<double>& var) {

  dt = var[0];
  dx = var[1];

  nx = var[2];
  nt = 0;

  c = var[3];
  l = var[4];
  r0 = var[5];
  j0 = var[6];

  e0 = var[7];
  w = var[8];

  step = 0;

  previousState = vector<double>(nx, 0.0);
  currentState = vector<double>(nx, 0.0);
}

vector<double> PDE::implicitEquation (vector<double>& nextState) {
  vector<double> result = vector<double>(nx-2, 0.0);

  double jx;
  double jt;
  double jtt;
  double s;

  double num;
  double denom;

  for (int i = 1; i < nx-1; i++) {
    if (i == 1) jx = (nextState[i+1] - 2.0*nextState[i]) / dx;
    else if (i == nx-1) jx = (nextState[i-1] - 2.0*nextState[i]) / dx;
    else jx = (nextState[i+1] - 2.0*nextState[i] + nextState[i-1]) / dx;
  
    num = j0*(nextState[i] - previousState[i]);
    num += fabs(nextState[i])*previousState[i] - fabs(previousState[i])*nextState[i];
    denom = (j0 - fabs(nextState[i])) * (j0 - fabs(previousState[i]));
    jt = -0.5*c*r0*j0/dt * num / denom;

    jtt = -l*c/(dt*dt) * (nextState[i] - 2.0*currentState[i] + previousState[i]);

    s = e0*w * cos(w*(step+1));

    result[i-1] = jx + jt + jtt + s;
  }

  return result;
}

vector<vector<double>> PDE::jacobian(vector<double>& nextState) {
  vector<vector<double>> result = vector<vector<double>>(nx-2, vector<double>(nx-2, 0.0));

  double jx = -2.0 / dx;
  double jt;
  double jtt;

  double jt1;
  double jt2;

  double sideDiagonal = 1.0 / dx;

  for (int i = 1; i < nx-1; i++) {
    jt1 = j0 + sgn(nextState[i])*previousState[i] - fabs(previousState[i]);
    jt1 /= j0 - fabs(nextState[i]);

    jt2 = j0*(nextState[i] - previousState[i]) + fabs(nextState[i])*previousState[i] - fabs(previousState[i])*nextState[i];
    jt2 *= sgn(nextState[i]) / pow(j0 - fabs(nextState[i]), 2);
    
    jt = -0.5*c*r0*j0/dt / (j0 - fabs(previousState[i]));

    jtt = - l*c/(dt*dt);

    result[i-1][i-1] = jx + jt + jtt;
    if (i != nx-2) result[i-1][i] = sideDiagonal;
    if (i != 1) result[i-1][i-2] = sideDiagonal;
  }
  
  return result;
}
