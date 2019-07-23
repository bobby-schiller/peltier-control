#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include "PID.h"
#include "SerialCom.h"
#include "Bk16XXPs.h"
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include <chrono>

double voltage;
double kp; // 3.0
double ki; // 0.5
double kd; // 19.5
double hot;
double cold;
double set_point;
double max_voltage = 12.5;
double go_time_temp = (max_voltage / kp);
double  duration = 200.0;
unsigned num_ntc = 2;

std::string arduinoPort = "/dev/ttyACM0";
std::string psPort = "/dev/ttyUSB0";

/*
 Split a string into a vector of strings by some char delimiter. Note that
 the delimiter should be enclosed by single quotes (eg. newline would be '\n').
*/
std::vector<std::string> parse(const std::string& s, char delimiter) {

   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);

   while (std::getline(tokenStream, token, delimiter)) {
      tokens.push_back(token);
   }
   return tokens;
}

/*
 Placeholder for functionality if there is a read error from the Arduino
*/
void readError() {
  std::cout<<"Read error encountered.";
}

/*
 @arguments User may specify the port for the Arduino and the power supply, respectively.
 Default settings are Arduino: "/dev/ttyACM0"; PS: "/dev/ttyUSB0"
 Example: "./peltier_loop /dev/ttyACMO /dev/ttyUSB0"
*/
int main(int argc, char *argv[]){
  
  // Check if the user set ports. Otherwise use defaults.
  if (argc == 3) {
    arduinoPort = argv[1];
    psPort = argv[2];
  }
  
  SerialCom Arduino(arduinoPort, B9600);
  Bk16XXPs PS(psPort);

  std::cout<<"Set point: ";
  std::cin>>set_point;
  std::cout<<"k_p: ";
  std::cin>>kp;
  std::cout<<"k_i: ";
  std::cin>>ki;
  std::cout<<"k_d: ";
  std::cin>>kd;

  Pid TC(&voltage, kp, ki, kd);
  TC.set_output_limits(1.0, max_voltage);

  std::string buf;
  bool temp_reached = false;

  while (true){
    Arduino.read(buf);	      
    
    // Each NTC outputs at least 4 characters, X.XX, with a space between each output
    if (buf.length() > 8*num_ntc){
      
      std::vector<std::string> readings = parse(buf,'\n');
      try {
	hot = stod(parse(readings[readings.size() - 2],' ')[0]);
	cold = stod(parse(readings[readings.size() - 2],' ')[1]);
      } catch (std::invalid_argument &err) {
	readError();
	continue;
      }

      if (abs(set_point - cold) < go_time_temp or temp_reached){
	temp_reached = true;
	if (TC.compute(cold, set_point, duration)){
	  std::cout<<voltage<<std::endl;
	  PS.setVoltage(voltage);
	  std::cout<<"Temperatures: " << hot << ", " << cold;
	  std::cout<<"Voltage: " <<voltage;
	}
      } else {
	PS.setVoltage(max_voltage);
      }
    }
    sleep(1);
  }
  return 0;
}



