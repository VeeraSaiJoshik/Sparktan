
#pragma once
#include "pros/misc.hpp"
#include "global.hpp"

/*
    Function Name : driveTrainFunction
    Author : Veera Unnam (Jo)
    Description : This function reads the joystick values from the controller and controls the drivetrain based on the specified drive mode, which is either analog or tankdrive
    Hardware : 
        1. frontRightMotor
        2. frontLeftMotor
        3. rearRightMotor
        4. rearLeftMotor
    Output : N/A
*/
void driveTrainFunction();

//^ Different Drive Modes
/*
    Function Name : tankDrive
    Author : Veera Unnam(Jo)
    Description : This function reads the analog values from the joy stick and controls the drive train according to the rules set by the Tank Drive methodology.
    Hardware :
        1. frontRightMotor
        2. frontLeftMotor
        3. rearRightMotor
        4. rearLeftMotor
    Input :
        1. leftJoyStick: this variable, based on the JoystickValues class, contains data regarding the X and Y displacement values of the left joystick
        2. rightJoyStick: this variable, based on the JoystickValues class, contains data regarding the X and Y displacement values of the right joystick
    Output : N/A
*/
void tankDrive(JoystickValues leftJoyStick, JoystickValues rightJoyStick);

/*
    Function Name : tankDrive
    Author : Veera Unnam(Jo)
    Description : This function reads the analog values from the joy stick and controls the drive train according to the rules set by the Arcade Drive methodology. This function allows
                  the driver to use either the left or right joystick to control the drive train.
    Hardware :
        1. frontRightMotor
        2. frontLeftMotor
        3. rearRightMotor
        4. rearLeftMotor
    Input :
        1. leftJoyStick: this variable, based on the JoystickValues class, contains data regarding the X and Y displacement values of the left joystick
        2. rightJoyStick: this variable, based on the JoystickValues class, contains data regarding the X and Y displacement values of the right joystick
    Output : N/A
*/
void arcadeDrive(JoystickValues joyStick);

//^ Drive Train 
/*
    Function Name : moveDriveTrain
    Author : Veera Unnam (Jo)
    Description : This function moves all 4 motors of the drive train at a certain speed given in volts.
    Hardware : 
        1. frontRightMotor
        2. frontLeftMotor
        3. rearRightMotor
        4. rearLeftMotor
    Input : 
        1. voltage : this variable holds a value from -125 to 125 and it dictates what dierction the drive train goes in and how many volts are supplied to the motor
    Output : N/A
*/
void moveDriveTrain(double voltage);

/*
    Function Name : brakeDriveTrain
    Author : Veera Unnam (Jo)
    Description : The brake drive train function stops the entire drive train in place
    Hardware :
        1. frontRightMotor 
        2. frontLeftMotor
        3. rearRightMotor
        4. rearLeftMotor
    Output : N/A
*/
void brakeDriveTrain();

/*
    Function Name : moveRightDrive
    Author : Veera Unnam (Jo)
    Description : this functions moves the right side of the drive train at a certain speed and in the specified directio
    Hardware :
        1. frontRightMotor
        2. rearRightMotor
    Output : N/A
*/
void moveRightDrive(int voltage);

/*
    Function Name : moveLeftDrive
    Author : Veera Unnam (Jo)
    Description : this functions moves the left side of the drive train at a certain speed and in the specified directio
    Hardware :
        1. frontLeftMotor
        2. rearLeftMotor
    Output : N/A
*/
void moveLeftDrive(int voltage);

/*
    Function Name : rotateDriveTrain
    Author : Veera Unnam (Jo)
    Description : this function rotates the entire drive train either clockwise or counter-clockwise at the specified speed
    Hardware :
        1. frontRightMotor 
        2. frontLeftMotor
        3. rearRightMotor
        4. rearLeftMotor
    Input : 
        1. voltage : this variable holds a value from -125 to 125 which is used to determine the direction and speed in which the chassis will rotate
    Output : N/A
*/
void rotateDriveTrain(double voltage);

/*
    Function Name : moveDriveTrainAccurate
    Author : Veera Unnam (Jo)
    Description : This function, specifically used in PID, is used to control the drive trains movement through millivolts offering more precise control
    Hardware :
        1. frontRightMotor 
        2. frontLeftMotor
        3. rearRightMotor
        4. rearLeftMotor
    Input : 
        1. voltage : this variable holds a value from -120000 to 120000 and it dictates what dierction the drive train goes in and how many milli-volts are supplied to the motor
    Output : N/A
*/
void moveDriveTrainAccurate(int millivolts);

/*
    Function Name : rotateDriveTrainAccurate
    Author : Veera Unnam (Jo)
    Description : this function rotates the entire drive train either clockwise or counter-clockwise at the specified speed
    Hardware :
        1. frontRightMotor 
        2. frontLeftMotor
        3. rearRightMotor
        4. rearLeftMotor
    Input : 
        1. voltage : this variable holds a value from -120000 to 120000 which is used to determine the direction and speed in which the chassis will rotate
    Output : N/A
*/
void rotateDriveTrainAccurate(int millivolts);

/*
    Function Name : getDriveTrainVoltage
    Author : Veera Unnam (Jo)
    Description : You can use this function to get the voltage of the entire drive train
    Logic : The function gets the voltage values of each motor in millivolts and takes the arithmetic mean
    Hardware :
        1. frontRightMotor 
        2. frontLeftMotor
        3. rearRightMotor
        4. rearLeftMotor
    Output : returns the arithmetic mean described above
*/
double getDriveTrainVoltage();

double getDriveTrainVelocity();

/*
    Function Name : moveDriveTrainWithVelocity
    Author : Veera Unnam (Jo)
    Description : This function, specifically used in PID, is used to control the drive trains movement through velocity and PID ensuring that the motors maintain a constant speed with little fluctuation
    Hardware :
        1. frontRightMotor 
        2. frontLeftMotor
        3. rearRightMotor
        4. rearLeftMotor
    Input : 
        1. voltage : this variable holds a value from -200 to 200 and it dictates what dierction the drive train goes in and how fast the motors are rotating
    Output : N/A
*/
void moveDriveTrainWithVelocity(int velocity);

/*
    Function Name : rotateDriveTrainWithVelocity
    Author : Veera Unnam (Jo)
    Description : this function rotates the entire drive train either clockwise or counter-clockwise at the specified speed. This function utilizes PID to ensure that the drive train maintains a constant speed
    Hardware :
        1. frontRightMotor 
        2. frontLeftMotor
        3. rearRightMotor
        4. rearLeftMotor
    Input : 
        1. velocity : this variable holds a value from -200 to 200 which is used to determine the direction and speed in which the chassis will rotate
    Output : N/A
*/
void rotateDriveTrainWithVelocity(int velocity);



