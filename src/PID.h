#ifndef PID_H
#define PID_H

#include<iostream>
#include<vector>
#include<numeric>
#include<cmath>

class PID {
 public:
  double Kp;
  double Ki;
  double Kd;
  
  int count;
  double error;
  const double tol = 0.01;
  double totalError;
  double best_err;
  double temp_error;
  
  const int n_opt = 100;
  const int n_acu = 9700;
  int val_i;
  
  std::vector<double> p;
  std::vector<double> dp;
//  std::vector<double>::iterator it;
  
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp_, double Ki_, double Kd_);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError(double cte);
  
  void Twiddle(int j);

 private:
  /**
   * PID Errors
   */
  double p_error;
  double i_error;
  double d_error;


  /**
   * PID Coefficients
   */ 

  double pre_cte;
//  bool last_cte_initialized;
  double intg_cte;
  

};

#endif  // PID_H
