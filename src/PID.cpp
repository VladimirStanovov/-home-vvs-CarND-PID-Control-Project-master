#include <iostream>
#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double newKp, double newKi, double newKd, double newdKp, double newdKi, double newdKd) {
  p_error = 0;
  i_error = 0;
  d_error = 0;
  sq_error = 0;
  iter = 0;
  bestErr = -1;
  ic = 0;
  state = 1;
  K[0] = newKp;
  K[1] = newKi;
  K[2] = newKd;
  dK[0] = newdKp;
  dK[1] = newdKi;
  dK[2] = newdKd;
}

void PID::UpdateError(double cte) {
  d_error = cte - p_error;
  if((cte < 0 && p_error > 0) || (cte > 0 && p_error < 0))
    i_error = 0;
  i_error += cte;
  p_error = cte;
  sq_error += cte*cte;
  iter++;
}

double PID::TotalError() {
  return K[0]*p_error + K[1]*i_error + K[2]*d_error;
}

void PID::ResetErrors()
{
  p_error = 0;
  i_error = 0;
  d_error = 0;
  sq_error = 0;
  iter = 0;
}

double PID::SumDK()
{
  return dK[0]+dK[1]+dK[2];
}

double PID::AvgError()
{
  if(iter != 0)
    return sq_error / iter;
  return 0;
}

void PID::Twiddle()
{
  if(bestErr == -1)
  {
    bestErr = AvgError();
    if(bestErr == 0)
      bestErr = -1;
    else
      K[ic] += dK[ic];
  }
  else
  {
    double newErr = AvgError();
    cout<<newErr<<"\t";
    if(newErr <= bestErr)
    {
      cout<<" < bestErr\t";
      bestErr = newErr;
      dK[ic] *= 1.1;
      ic = (ic+1)%3;
      //if(ic == 1)
        // ic = 2;
      state = 1;
    }
    else if(state == 1)
    {
      cout<<" > bestErr, state = 2\t";
      K[ic] -= 2*dK[ic];
      state = 2;
      return;
    }
    else
    {
      cout<<" > bestErr, state = 1\t";
      K[ic] += dK[ic];
      dK[ic] *= 0.9;
      ic = (ic+1)%3;
      //if(ic == 1)
        // ic = 2;
      state = 1;
    }
    K[ic] += dK[ic];
  }
}

