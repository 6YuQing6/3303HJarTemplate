using namespace vex;

extern brain Brain;

//To set up a motor called LeftFront here, you'd use
//extern motor LeftFront;

//Add your devices below, and don't forget to do the same in robot-config.cpp:

extern digital_out PistonTop; // formally piston
extern digital_out PistonBottom; // formally piston2
extern motor MotorTopOut; // formally motor10
extern motor MotorBottomInRubber; // formally motor21
extern motor MotorIntakeMiddle; // formally motor1


void  vexcodeInit( void );