# CarND-PID-Control-Project
Self-Driving Car Engineer Nanodegree Program

Introduction
The purpose of this project was to learn how to use a PID controller to control the car, and learn how PID paramteters affect the CTE error.

Rubric Points appliance:

Compilation:
The code can compile and run the car, even not that smoothly yet. 

Implementation:
The PID precedure follows what was taught in the lessons. 

Reflection:

Describe the effect each of the P, I, D components had in your implementation:
The P, or "proportional", directly affect the car's behavior, wave the car according to the cte value, and the car will wave more if the P value increase.

The D, or "differential", will compensate the P's tendency to wave around center line. A properly tuned D parameter will cause the car to approach the center line smoothly without waving.

The I, or "integral", will compensate a drift  CTE from the center line.

Describe how the final hyperparameters were chosen.
Final Parameters I get is [Kp, Ki, Kd] = [0.275291, 1.98e-09, 2.52578].
As I can't find out the communication mechanism between the PID and the simulator, I can't implement the same twiddle method as introduced in the lesson, as I can't find a way to implement internal run inside the loop. So I used a weired way to twiddle the parameter, and it might find a better parameter, but can't converge. 
First I manually tuned the parameters, as if it was randomly chosen, it will easilly run off the road, and can never come back again, and I also checked other guys's tuned parameters to take a try. 
Once I found the parameters that the vehicle can stay in the track, I try to implement Twiddle. 
The weired method I used is as following:
1) It seems 9800 steps is about one full lap, I think to compare the totalError with the same base, I need one full lap totalError. For this reason I use n_opt with 100 steps to converge to the center line, and n_acu 9700 steps to calculate the totalError. 
2) For every lap, I change the parameter one time to see how the totalError looks, and then update the parameter.
3) For every paramter, I run certain laps to update it, as in the code, 10 laps for each parameter to update, and then choose the parameter that creates the lowest totalError.
But it can't converge, if I can know how the communication mechanism between the PID and the simulator I can implement the same twiddle method as in the lesson.

Simulation:
The vehicle can successfully drive a lap around the track. No tire leave the drivable portion of the track surface. The car may not pop up onto ledges or roll over any surfaces that would otherwise be considered unsafe (if humans were in the vehicle).
The simulator can't record the video as before, I don't know why.



