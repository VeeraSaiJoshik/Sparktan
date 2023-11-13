
#pragma once
#include "pros/misc.hpp"
#include "global.h"
void driveTrainFunction();
//^ Different Drive Modes
void tankDrive(JoystickValues leftJoyStick, JoystickValues rightJoyStick);
void arcadeDrive(JoystickValues joyStick);
//^ Drive Train 
void moveDriveTrain(double voltage);
void brakeDriveTrain();
void moveRightDrive(double voltage);
void moveLeftDrive(double voltage);
void rotateDriveTrain(double voltage);


