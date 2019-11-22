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
  
  p.push_back(Kp);
  p.push_back(Ki);
  p.push_back(Kd);
  
  dp.push_back(0.01);
  dp.push_back(0.000000001);
  dp.push_back(0.01);
//  dp.assign(3, 0.01);
  
  p_error = 0;
  i_error = 0;
  d_error = 0;
  error = 0;
  
  pre_cte = 0;
//  last_cte_initialized = false;
  intg_cte = 0;
  
  count = 0;
  
  val_i = 0;
  
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

void PID::Twiddle(int j) {
  
//  dp.push_back(0.1*Kp+0.001);
//  dp.push_back(0.1*Kd+0.001);
//  dp.push_back(0.1*Ki+0.001);
  std::cout<<"twiddle starts:"<<std::endl;
  if (accumulate(dp.begin(), dp.end(),0.0) > tol) {
    
//    int i = count / (n_opt + n_acu) - 1;
//    int j = i % 3;

//    p[j] += dp[j];
//    for(j = 0; j < 3; ++j) {
//      p[j] += dp[j];
//      double err = totalError;
//    temp_error = totalError;
    std::cout<<"totalError ="<<totalError<<std::endl;
    if (totalError < best_err) {
      best_err = totalError;
      p[j] += dp[j];
      dp[j] *= 1.1;
      val_i = 0;
    }
    else if (val_i == 0) {
      p[j] -= 2 * (dp[j]/1.1);
      dp[j] /= 1.1;
      val_i = 1;
    }
    else {
      p[j] += dp[j];
      dp[j] *= 0.9;
      val_i = 0;
    }
//    if (temp_error < best_err) {
//      best_err = temp_error;
//      dp[j] *= 1.1;
//    }
//
//    else {
//      p[j] -= 2 * dp[j];
//      temp_error = totalError;
//      if (temp_error < best_err) {
//        best_err = temp_error;
//        dp[j] *= 1.1;
//      }
//      else {
//        p[j] += dp[j];
//        dp[j] *= 0.9;
//      }
//    }
    std::cout<<"p["<<j<<"] ="<<p[j]<<std::endl;
    std::cout<<"dp["<<j<<"] ="<<dp[j]<<std::endl;
  }
//    Kp = p[0];
//    Kd = p[1];
//    Ki = p[2];
//    return p;
  
}
