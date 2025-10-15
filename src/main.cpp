#include "vex.h"

using namespace vex;
competition Competition;

motor leftMotorA = motor(PORT18, ratio6_1, true);
motor leftMotorB = motor(PORT2, ratio6_1, true);
motor leftMotorC = motor(PORT12, ratio6_1, true);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB, leftMotorC);
motor rightMotorA = motor(PORT16, ratio6_1, false);
motor rightMotorB = motor(PORT11, ratio6_1, false);
motor rightMotorC = motor(PORT20, ratio6_1, false);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB,rightMotorC);

// inertial intertialSensor = inertial(PORT17); 
// smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, intertialSensor, 219.44, 295, 40, mm, 1);
controller Controller1 = controller(primary);


/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors. In VEXcode Pro V5, you can do this using the graphical          */
/*  configurer port icon at the top right. In the VSCode extension, you'll   */
/*  need to go to robot-config.cpp and robot-config.h and create the         */
/*  motors yourself by following the style shown. All motors must be         */
/*  properly reversed, meaning the drive should drive forward when all       */
/*  motors spin forward.                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your motors.                                     */
/*---------------------------------------------------------------------------*/

Drive chassis(

//Pick your drive setup from the list below:
//ZERO_TRACKER_NO_ODOM
//ZERO_TRACKER_ODOM
//TANK_ONE_FORWARD_ENCODER
//TANK_ONE_FORWARD_ROTATION
//TANK_ONE_SIDEWAYS_ENCODER
//TANK_ONE_SIDEWAYS_ROTATION
//TANK_TWO_ENCODER
//TANK_TWO_ROTATION
//HOLONOMIC_TWO_ENCODER
//HOLONOMIC_TWO_ROTATION
//
//Write it here:
ZERO_TRACKER_NO_ODOM,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

//Left Motors:
LeftDriveSmart,

//Right Motors:
RightDriveSmart,

//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT17,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
3.25,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
0.6,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
360,

/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT1,     -PORT2,

//LB:      //RB: 
PORT3,     -PORT4,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
3,

//Input the Forward Tracker diameter (reverse it to make the direction switch):
2.75,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
-2,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
1,

//Sideways tracker diameter (reverse to make the direction switch):
-2.75,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
5.5

);

int current_auton_selection = 0;
bool auto_started = false;

/**
 * Function before autonomous. It prints the current auton number on the screen
 * and tapping the screen cycles the selected auton by 1. Add anything else you
 * may need, like resetting pneumatic components. You can rename these autons to
 * be more descriptive, if you like.
 */

void pre_auton() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants();

  while(!auto_started){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5, 20, "JAR Template v1.2.0");
    Brain.Screen.printAt(5, 40, "Battery Percentage:");
    Brain.Screen.printAt(5, 60, "%d", Brain.Battery.capacity());
    Brain.Screen.printAt(5, 80, "Chassis Heading Reading:");
    Brain.Screen.printAt(5, 100, "%f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5, 120, "Selected Auton:");
    switch(current_auton_selection){
      case 0:
        Brain.Screen.printAt(5, 140, "Auton 1");
        break;
      case 1:
        Brain.Screen.printAt(5, 140, "Auton 2");
        break;
      case 2:
        Brain.Screen.printAt(5, 140, "Auton 3");
        break;
      case 3:
        Brain.Screen.printAt(5, 140, "Auton 4");
        break;
      case 4:
        Brain.Screen.printAt(5, 140, "Auton 5");
        break;
      case 5:
        Brain.Screen.printAt(5, 140, "Auton 6");
        break;
      case 6:
        Brain.Screen.printAt(5, 140, "Auton 7");
        break;
      case 7:
        Brain.Screen.printAt(5, 140, "Auton 8");
        break;
    }
    if(Brain.Screen.pressing()){
      while(Brain.Screen.pressing()) {}
      current_auton_selection ++;
    } else if (current_auton_selection == 8){
      current_auton_selection = 0;
    }
    wait(10, msec);
  }
}

/**
 * Auton function, which runs the selected auton. Case 0 is the default,
 * and will run in the brain screen goes untouched during preauton. Replace
 * drive_test(), for example, with your own auton function you created in
 * autons.cpp and declared in autons.h.
 */
void loader() {
  chassis.set_heading(0);
  // starts directly in front of loader for testing
  LeftDriveSmart.setVelocity(100, percent);
  RightDriveSmart.setVelocity(100, percent);
  PistonBottom.set(true);
  MotorIntakeMiddle.spin(forward, 100, percent);
  MotorBottomInRubber.spin(reverse, 100, percent);
  // intakes from loader
  chassis.set_drive_exit_conditions(1, 300, 500);
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.drive_distance(17);
  wait(0.6, seconds);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  // MotorBottomInRubber.stop();
  // MotorIntakeMiddle.stop();
  chassis.drive_distance(-10);
  chassis.turn_to_angle(-190);
  PistonTop.set(false);
  wait(0.4, seconds);
  PistonBottom.set(false);
  chassis.drive_distance(16);

  // loads long goal
  MotorIntakeMiddle.spin(forward, 90, percent);
  MotorBottomInRubber.spin(forward, 100, percent);
  MotorTopOut.spin(forward, 100, percent);
}

void rightMiddleLoader() {
 
  chassis.set_drive_constants(9, 1.5, 0, 10, 0);
  // chassis.turn_to_angle(8);
  MotorIntakeMiddle.spin(forward, 60, percent);
  MotorBottomInRubber.spin(reverse, 100, percent);
  PistonTop.set(false);
  LeftDriveSmart.setVelocity(20, percent);
  RightDriveSmart.setVelocity(20, percent);
  chassis.drive_distance(13);
  chassis.turn_to_angle(30);
  chassis.drive_distance(13.5, 30, 2, 2);
  wait(0.5, seconds);
  // MotorIntakeMiddle.stop();
  // MotorBottomInRubber.stop();
  // go to middle goal across
  LeftDriveSmart.setVelocity(35, percent);
  RightDriveSmart.setVelocity(35, percent);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(9);
  MotorIntakeMiddle.spin(reverse, 60, percent);
  MotorBottomInRubber.spin(forward, 60, percent);
  
  // MotorTopOut.spin(reverse,70,percent);
  wait(2.1, seconds);
  LeftDriveSmart.setVelocity(90, percent);
  RightDriveSmart.setVelocity(90, percent);
  chassis.drive_distance(2.5);
  // chassis.drive_distance(1);
  // wait(0.5, seconds);
  //MotorIntakeMiddle.stop();
  //MotorBottomInRubber.stop();
  //MotorTopOut.stop();
  chassis.drive_distance(-46.5);
  chassis.turn_to_angle(180);
  // chassis.drive_distance(-5);
  loader();

}

void leftMiddleTest() {
  
  chassis.set_drive_constants(9, 1.5, 0, 10, 0);
  // chassis.turn_to_angle(8);
  MotorIntakeMiddle.spin(forward, 60, percent);
  MotorBottomInRubber.spin(reverse, 100, percent);
  PistonTop.set(false);
  LeftDriveSmart.setVelocity(20, percent);
  RightDriveSmart.setVelocity(20, percent);
  chassis.drive_distance(13);
  chassis.turn_to_angle(-30);
  chassis.drive_distance(12, -30, 2, 2);
  wait(0.5, seconds);
  // MotorIntakeMiddle.stop();
  // MotorBottomInRubber.stop();
  // go to middle goal across
  LeftDriveSmart.setVelocity(35, percent);
  RightDriveSmart.setVelocity(35, percent);
  chassis.turn_to_angle(45);
  chassis.drive_distance(11);
  MotorIntakeMiddle.spin(forward, 70, percent);
  MotorBottomInRubber.spin(forward, 70, percent);
  MotorTopOut.spin(reverse,70,percent);
  wait(2.1, seconds);
  LeftDriveSmart.setVelocity(90, percent);
  RightDriveSmart.setVelocity(90, percent);
  // chassis.drive_distance(1);
  // wait(0.5, seconds);
  //MotorIntakeMiddle.stop();
  //MotorBottomInRubber.stop();
  //MotorTopOut.stop();
  chassis.drive_distance(-44.5);
  chassis.turn_to_angle(180);
  // chassis.drive_distance(-5);
  loader();

}


// place drivetrain inside of parking zone and run
void skillsCheese() {
  MotorIntakeMiddle.spin(forward, 100, percent);
}

// place drivetrain next to parking zone and it will drive into the zone, pushing balls out
void skillsSlightCheese() {
  chassis.set_drive_constants(12, 1.5, 0, 10, 0);
  chassis.drive_distance(-20);
}

// copy auton C 
// https://docs.google.com/presentation/d/1kuT2zs910XhQ_iO0IqNDbCkZTuXEhhGNiHDB0uZsjT4/edit?usp=sharing 
void skillsFull() {

}


void autonomous(void) {
  auto_started = true;
  Brain.Screen.print("HIHIHIHI");
  rightMiddleLoader();
  switch(current_auton_selection){ 
    case 0:
      skillsCheese();
      break;
    case 1:         
      skillsSlightCheese();
      break;
    case 2:
      skillsFull();
      break;
 }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
bool RemoteControlCodeEnabled = true;

// define variables used for controlling motors based on controller inputs
bool Controller1LeftShoulderControlMotorsStopped = true;
bool Controller1RightShoulderControlMotorsStopped = true;
bool Controller1XBButtonsControlMotorsStopped = true;
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;
bool pistonToggled = false;
bool pistonButtonPrev = false;
bool piston2Toggled = false;
bool piston2ButtonPrev = false;

// Add new definitions for motor state
enum MotorDirection { STOPPED = 0, CLOCKWISE = 1, COUNTERCLOCKWISE = 2 };
int motor1State = CLOCKWISE;         // Motor4 (Motor1) starts clockwise
int motor10State = CLOCKWISE;   // Motor10 starts counterclockwise
bool motor1UpPrev = false, motor1DownPrev = false;
bool motor10L1Prev = false, motor10L2Prev = false;
void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    if(RemoteControlCodeEnabled) {
      // Motor1 control using arrow keys (Up/Down)
      bool motor1UpCurr = Controller1.ButtonUp.pressing();
      bool motor1DownCurr = Controller1.ButtonDown.pressing();
      if (motor1UpCurr && !motor1UpPrev) {
        if(motor1State == CLOCKWISE) {
            motor1State = STOPPED;
          } else {
            motor1State = CLOCKWISE;
          }
      }
      if(motor1DownCurr && !motor1DownPrev) {
          if(motor1State == COUNTERCLOCKWISE) {
            motor1State = STOPPED;
          } else {
            motor1State = COUNTERCLOCKWISE;
          }
        }
      motor1UpPrev = motor1UpCurr;
      motor1DownPrev = motor1DownCurr;
      MotorIntakeMiddle.setVelocity(100, pct);
      if(motor1State == CLOCKWISE) {
        MotorIntakeMiddle.spin(forward);
      } else if(motor1State == COUNTERCLOCKWISE) {
        MotorIntakeMiddle.spin(reverse);
      } else {
        MotorIntakeMiddle.stop();
      }

      // Control for Motor10 using L1 and L2 keys
      bool motor10L1Curr = Controller1.ButtonL1.pressing();
      bool motor10L2Curr = Controller1.ButtonL2.pressing();
      if(motor10L1Curr && !motor10L1Prev) {
        if(motor10State == CLOCKWISE) {
          motor10State = STOPPED;
        } else {
          motor10State = CLOCKWISE;
        }
      }
      if(motor10L2Curr && !motor10L2Prev) {
        if(motor10State == COUNTERCLOCKWISE) {
          motor10State = STOPPED;
        } else {
          motor10State = COUNTERCLOCKWISE;
        }
      }
      motor10L1Prev = motor10L1Curr;
      motor10L2Prev = motor10L2Curr;
      
      MotorTopOut.setVelocity(100, pct);
      if(motor10State == CLOCKWISE) {
        MotorTopOut.spin(forward);
      } else if(motor10State == COUNTERCLOCKWISE) {
        MotorTopOut.spin(reverse);
      } else {
        MotorTopOut.stop();
      }

      // Control for Motor21 using R1/R2
      if (Controller1.ButtonR1.pressing()) {
        MotorBottomInRubber.setVelocity(100, pct);
        MotorBottomInRubber.spin(forward);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonR2.pressing()) {
        MotorBottomInRubber.setVelocity(100, pct);
        MotorBottomInRubber.spin(reverse);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (!Controller1RightShoulderControlMotorsStopped) {
        MotorBottomInRubber.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1RightShoulderControlMotorsStopped = true;
      }
      // piston toggle thingy idk what to put here
      bool pistonButtonCurr = Controller1.ButtonA.pressing();
      if (pistonButtonCurr && !pistonButtonPrev) { 
        pistonToggled = !pistonToggled;
        PistonTop.set(pistonToggled);
      }
      pistonButtonPrev = pistonButtonCurr;

      bool piston2ButtonCurr = Controller1.ButtonB.pressing();
      if (piston2ButtonCurr && !piston2ButtonPrev) {
        piston2Toggled = !piston2Toggled;
        PistonBottom.set(piston2Toggled);
      }
      piston2ButtonPrev = piston2ButtonCurr; 

      chassis.control_arcade();

      wait(20, msec); // Sleep the task for a short amount of time to
    }              // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
