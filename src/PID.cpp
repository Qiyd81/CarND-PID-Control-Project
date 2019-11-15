#include "PID.h"

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;
//  tol = 0.2;
  
  dp.assign(3, 0.2);
  
  p_error = 0;
  i_error = 0;
  d_error = 0;
  error = 0;
  
  pre_cte = 0;
//  last_cte_initialized = false;
  intg_cte = 0;
  
  count = 0;
  
  totalError = 0;
  best_err = std::numeric_limits<double>::max();

}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
//  if (!last_cte_initialized) {
//    last_cte = cte;
//    last_cte_initialized = true;
//  }
  intg_cte += cte;
  
  p_error = -Kp * cte;
  i_error = -Ki * intg_cte;
  d_error = -Kd * (cte - pre_cte);
  error = p_error + d_error + i_error;
  
  pre_cte = cte;
  
  count += 1;
//  return error, count;
}

double PID::TotalError(double cte) {
  /**
   * TODO: Calculate and return the total error
   */
//  if (count % (n_opt + n_acu) > n_opt) {
//    totalError += pow(cte, 2);
//  }
  totalError += pow(cte, 2);
//  double totalError = p_error + i_error + d_error;
  
  return totalError;  // TODO: Add your total error calc here!
}

void PID::Twiddle() {

  p.push_back(Kp);
  p.push_back(Kd);
  p.push_back(Ki);
  
//  dp.push_back(0.1*Kp+0.001);
//  dp.push_back(0.1*Kd+0.001);
//  dp.push_back(0.1*Ki+0.001);
  
  while (accumulate(dp.begin(), dp.end(),0) > tol) {
    for(int i = 0; i < 3; ++i) {
      p[i] += dp[i];
      double err = totalError;
      
      if (err < best_err) {
        best_err = err;
        dp[i] *= 1.1;
      }
      else {
        p[i] -= 2* dp[i];
        err = totalError;
        if (err < best_err) {
          best_err = err;
          dp[i] *= 1.1;
        }
        else {
          p[i] += dp[i];
          dp[i] *= 0.9;
        }
      }
    }
    Kp = p[0];
    Kd = p[1];
    Ki = p[2];
//    return p, best_err;
  }
  
}
