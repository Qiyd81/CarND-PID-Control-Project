#include <math.h>
#include <uWS/uWS.h>
#include <iostream>
#include <string>
#include "json.hpp"
#include "PID.h"

// for convenience
using nlohmann::json;
using std::string;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
string hasData(string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != string::npos) {
    return "";
  }
  else if (b1 != string::npos && b2 != string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

int main() {
  uWS::Hub h;

  PID pid;
  /**
   * TODO: Initialize the pid variable.
   */
  pid.Init(0.30, 0.0, 2.5);

  h.onMessage([&pid](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, 
                     uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2') {
      auto s = hasData(string(data).substr(0, length));

      if (s != "") {
        auto j = json::parse(s);

        string event = j[0].get<string>();

        if (event == "telemetry") {
          // j[1] is the data JSON object
          double cte = std::stod(j[1]["cte"].get<string>());
          double speed = std::stod(j[1]["speed"].get<string>());
          double angle = std::stod(j[1]["steering_angle"].get<string>());
          double steer_value;
          /**
           * TODO: Calculate steering value here, remember the steering value is
           *   [-1, 1].
           * NOTE: Feel free to play around with the throttle and speed.
           *   Maybe use another PID controller to control the speed!
           */
//          pid.UpdateError(cte);
//          steer_value = pid.error;
          if (pid.count % (pid.n_opt + pid.n_acu) <= pid.n_opt) {
            pid.UpdateError(cte);
            steer_value = pid.error;
          }
          else if (pid.count % (pid.n_opt + pid.n_acu) > pid.n_opt) {
            pid.UpdateError(cte);
            steer_value = pid.error;
            pid.TotalError(cte);
            std::cout<<"total error before twiddle ="<<pid.totalError<<std::endl;
          }
          if ((pid.count % (pid.n_opt + pid.n_acu) == 0) && pid.count != 0) {
            pid.Twiddle();
            pid.totalError = 0;
            std::cout<<"pid.count ="<<pid.count<<std::endl;
            std::cout<<"Kp ="<<pid.Kp<<"\t"<<"Kd ="<<pid.Kd<<"\t"<<"Ki ="<<pid.Ki<<std::endl;
            std::cout<<"p[0] ="<<pid.p[0]<<"\t"<<"p[1] ="<<pid.p[1]<<"\t"<<"p[2] ="<<pid.p[2]<<std::endl;
            
            // DEBUG
            std::cout << "CTE: " << cte << " Steering Value: " << steer_value << std::endl;
          }
          
//          std::cout<<"pid.count ="<<pid.count<<std::endl;
//          std::cout<<"Kp ="<<pid.Kp<<"\t"<<"Kd ="<<pid.Kd<<"\t"<<"Ki ="<<pid.Ki<<std::endl;
//
//
//          // DEBUG
//          std::cout << "CTE: " << cte << " Steering Value: " << steer_value
//                    << std::endl;
          
//          //Do conditional throttling based on cte
//          double throttle = 0.30;
//
//          if (fabs(cte) > 3.0) {
//            throttle = 0.05;
//          }
//          else if (fabs(cte) > 1.5) {
//            throttle = 0.10;
//          }

          json msgJson;
          msgJson["steering_angle"] = steer_value;
          msgJson["throttle"] = 0.3;
          auto msg = "42[\"steer\"," + msgJson.dump() + "]";
          std::cout << msg << std::endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }  // end "telemetry" if
      } else {
        // Manual driving
        string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }  // end websocket message if
  }); // end h.onMessage

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, 
                         char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port)) {
    std::cout << "Listening to port " << port << std::endl;
  } else {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  
  h.run();
}
