#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
  double sq_error;
  double bestErr;

  /*
  * Coefficients
  */
  double K[3];
  double dK[3];
  int iter;
  int ic;
  int state;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd,  double newdKp, double newdKi, double newdKd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  double SumDK();
  void ResetErrors();
  double AvgError();
  void Twiddle();
};

#endif /* PID_H */
