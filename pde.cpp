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

  for (int i = 0; i < nx-2; i++) {
    if (i == 0) jx = (nextState[i+1] - 2.0*nextState[i]) / dx;
    else if (i == nx-3) jx = (nextState[i-1] - 2.0*nextState[i]) / dx;
    else jx = (nextState[i+1] - 2.0*nextState[i] + nextState[i-1]) / dx;
  
    num = j0*(nextState[i] - previousState[i]);
    num += fabs(nextState[i])*previousState[i] - fabs(previousState[i])*nextState[i];
    denom = (j0 - fabs(nextState[i])) * (j0 - fabs(previousState[i]));
    jt = -0.5*c*r0*j0/dt * num / denom;

    jtt = -l*c/(dt*dt) * (nextState[i] - 2.0*currentState[i] + previousState[i]);

    s = e0*w * cos(w*(step+1));

    result[i] = jx + jt + jtt + s;
  }

  return result;
}
