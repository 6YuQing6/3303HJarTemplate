#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen.
brain  Brain;
digital_out PistonTop = digital_out(Brain.ThreeWirePort.A);
digital_out PistonBottom = digital_out(Brain.ThreeWirePort.B);
motor MotorTopOut = motor(PORT10, ratio18_1, false); // forward to outtake high, reverse to outtake middle
motor MotorBottomInRubber = motor(PORT21, ratio18_1, false); // forward to outtake to bottom, reverse to intake into hopper
motor MotorIntakeMiddle = motor(PORT4, ratio6_1, false); // forward to intake ball / outtake middle, reverse to outake bottom

//The motor constructor takes motors as (port, ratio, reversed), so for example
//motor LeftFront = motor(PORT1, ratio6_1, false);

//Add your devices below, and don't forget to do the same in robot-config.h:


void vexcodeInit( void ) {
  // nothing to initialize
}