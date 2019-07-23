#include "PID.h"
using namespace std::chrono;

Pid::Pid(double* Output, double Kp, double Ki, double Kd){
  myOutput = Output;
  sample_time = 100.0;
  Pid::set_tunings(Kp, Ki, Kd);
  first_compute = true;
  output_sum = 0;
}

bool Pid::compute(double input, double set_point, double duration){
  if (duration >= sample_time){
    double error = input - set_point;
    double delta_error = error - last_error;
    output_sum += (ki * error);
    output = (kp * error) + output_sum + (delta_error * kd);
    if(output > out_max) output = out_max;
    else if(output < out_min) output = out_min;		
    *myOutput = output;
    last_error = error;
    first_compute = false;
    return true;
  } else {
    return false;
  }
}

void Pid::set_output_limits(double min, double max){
  out_min = min;
  out_max = max;
}

void Pid::set_tunings(double Kp, double Ki, double Kd){
  double sample_time_sec = sample_time / 1000;
  kp = Kp;
  ki = Ki * sample_time_sec;
  kd = Kd / sample_time_sec;
}

void Pid::set_sample_time(double new_time){
  sample_time = new_time;
}
	
double Pid::get_kp(){
  return kp;
}

double Pid::get_ki(){
  return ki;
}

double Pid::get_kd(){
  return kd;
}
		
		
