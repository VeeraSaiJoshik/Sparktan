#include "main.h"
#include "pros/motors.h"

using namespace pros;

double PI = 3.141592653;
//? Drive Train Motor
Motor frontRightMotor(frontRightMotorPort, E_MOTOR_GEAR_GREEN, true);
Motor frontLeftMotor(rearRightMotorPort, E_MOTOR_GEAR_GREEN, false);
Motor rearRightMotor(frontLeftMotorPort, E_MOTOR_GEAR_GREEN, true);
Motor rearLeftMotor(rearLeftMotorPort, E_MOTOR_GEAR_GREEN, false);
//? Object Interaction Motor
Motor intakeMotor(intakeMotorPort, E_MOTOR_GEAR_BLUE, false);
Motor catapultMotor(catapultMotorPort, E_MOTOR_GEAR_RED, false);
Motor liftMotor(liftMotorPort, E_MOTOR_GEAR_RED, false);
pros::ADIDigitalOut piston (wingsPort);
//? Button Class
ButtonClass switchDriveTrainButton = ButtonClass(DIGITAL_A);
ButtonClass matchLoadButton = ButtonClass(DIGITAL_B);
ButtonClass extendWings = ButtonClass(DIGITAL_UP);
//? Main Variables
DriveTrainMode driveTrainMode = Arcade;
Controller brain = Controller(CONTROLLER_MASTER);
ADIDigitalIn catapultLimitSwitch(1);
bool catapultRunning = false;
bool wingsExtended = false;
IMU imuController(imuPort);
std::string autonCommandStringEncoded = ""; // <- Insert the required command for auton over here
