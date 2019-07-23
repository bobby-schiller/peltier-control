#import <unistd.h>
#import <stdlib.h>
#include <getopt.h>
#import "Bk16XXPs.h"
#import <iostream>
#import <string>

int main() {
  Bk16XXPs Ps("/dev/ttyUSB0");
  std::cout<<Ps.getVoltageReading();
}
