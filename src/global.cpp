#include "main.h"
#include "pros/motors.h"

using namespace pros;

#define frontRightMotorPort 2
#define rearRightMotorPort 3
#define frontLeftMotorPort 4
#define rearLeftMotorPort 5
#define imuPort 1

double PI = 3.141592653;
Motor frontRightMotor(frontRightMotorPort, E_MOTOR_GEAR_GREEN, true);
Motor frontLeftMotor(rearRightMotorPort, false);
Motor rearRightMotor(frontLeftMotorPort, true);
Motor rearLeftMotor(rearLeftMotorPort, false);
DriveTrainMode driveTrainMode = Arcade;
Controller brain = Controller(CONTROLLER_MASTER);
IMU imuController(imuPort);