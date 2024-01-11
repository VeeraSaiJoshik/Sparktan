#include "main.h"
#include "pros/motors.h"

using namespace pros;

double PI = 3.141592653;
//? Drive Train Motor
Motor frontRightMotor(frontRightMotorPort, E_MOTOR_GEAR_GREEN, true);
Motor frontLeftMotor(frontLeftMotorPort, E_MOTOR_GEAR_GREEN, false);
Motor rearRightMotor(rearRightMotorPort, E_MOTOR_GEAR_GREEN, true);
Motor rearLeftMotor(rearLeftMotorPort, E_MOTOR_GEAR_GREEN, false);
//? Object Interaction Motor
Motor intakeMotor(intakeMotorPort, E_MOTOR_GEAR_BLUE, true);
//Motor catapultMotor(catapultMotorPort, E_MOTOR_GEAR_RED, false);
Motor liftMotor(liftMotorPort, E_MOTOR_GEAR_RED, false);
Motor rachetMotor(rachetMotorPort, E_MOTOR_GEAR_RED, false);
Motor catapultMotor(puncherPort, E_MOTOR_GEAR_RED, false);
//? Button Class
ButtonClass switchDriveTrainButton = ButtonClass(DIGITAL_A);
ButtonClass matchLoadButton = ButtonClass(DIGITAL_B);
ButtonClass lockLiftButton = ButtonClass(DIGITAL_DOWN);
//? Main Variables
DriveTrainMode driveTrainMode = Tank;
Controller brain = Controller(CONTROLLER_MASTER);
ADIDigitalIn catapultLimitSwitch(1);
bool catapultRunning = false;
IMU imuController(imuPort);
std::string autonCommandStringEncoded = ""; // <- Insert the required command for auton over here
int armTotalTicks = 6000;
//& Odometry Variables
//* Global Location Variable
double globalX = 0;
double globalY = 0;
//* Tracker Variables
double thetaPrevious = 0;
//* constant variables
double degToRad = PI/180;
double distanceBackWheelToCenter = 0;
double distanceLeftWheelToCenter = 0;
double distanceRightWheelToCenter = 0;
double wheelRadius = 0;
//* sensor variables
OdometryPod rightPod = OdometryPod(1, 2, true, wheelRadius, distanceRightWheelToCenter);
OdometryPod leftPod = OdometryPod(3, 4, false, wheelRadius, distanceRightWheelToCenter);
OdometryPod backPod = OdometryPod(5, 6, true, wheelRadius, distanceRightWheelToCenter);