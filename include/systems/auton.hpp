#pragma once
#include "main.h"
//? Robot Movement Functions
/*
Function Name : moveForward
Author : Veera Unnam (Jo)
Description : This function moves the entire chasis forward or backward by the given inches.
Logic : What this function does it uses the circumference formula and some convesions to convert inches to rotational ticks. This rotational
ticks are then passed on to each of the motors in the drive train using the move_relative function. The function the runs a for loop
until the goal tick is reached or 2 seconds have passed.
Hardware : 
    - frontRightMotor
    - frontLeftMotor
    - rearRightMotor
    - rearLeftMotor
Input :
    1. Inches : this function takes a double in inches which is how much the robot will move forward
Output : <Description of what the function returns. This field can be emmited if the function is of type "void">
*/
void moveForward(double inches);

/*
Function Name : rotateTo
Author :  Veera Unnam (Jo)
Description : This function rotates the robot to the given degree. The degrees are all relative to the angle that the robot started in 
Logic : This function first calculates the angular error to get from the current angle to the target angle in degrees. Then the program
passes that data into the PID controller which then converts the error into voltages that can be passed on to the drive train. This proces
is repeated in a while loop until the robot reaches the target angle.
Hardware : 
    - frontRightMotor
    - frontLeftMotor
    - rearRightMotor
    - rearLeftMotor
    - IMUController
Bugs :
    1. constants : You have to fine tune the constants a bit more
Input : 
    1. degrees : this is an integer that tells the robot how many degrees to turn
*/
void rotateTo(double degrees);

/*
    Function Name : runIntake
    Author : Veera Unnam (Jo)
    Description : This function runs the intake arm in the clockwise direction for a certain amount of time
    Logic : The function simply sets the voltage of the intake motor to 125 volts, adds a delay for x milliseconds, and stops the motor after that delay
    Hardware : 
        - intakeMotor
    Input : 
        1. milliseconds : this is an integer that holds a value regarding how long the intake motor runs in milliseconds
*/
void runIntake(int milliseconds);

/*
    Function Name : runOuttake
    Author : Veera Unnam (Jo)
    Description : This function runs the intake arm in the counter clockwise direction for a certain amount of time
    Logic : The function simply sets the voltage of the intake motor to -125 volts, adds a delay for x milliseconds, and stops the motor after that delay
    Hardware : 
        - intakeMotor
    Input : 
        1. milliseconds : this is an integer that holds a value regarding how long the intake motor runs in milliseconds
*/
void runOuttake(int milliseconds);

/*
    Function Name : haltIntakeOuttake()
    Author : Veera Unnam (Jo)
    Description : This function can be used to immediately halt the intake motors. This functionc an be used as a fail safe or during auton.
    Hardware :
        - intakeMotor
*/
void haltIntakeOutake();

/*
    Function Name : shoveIn
    Author : Veera Unnam (Jo)
    Description : This function runs some commands to shove the triball under the net
    Logic : The motor simply runs the drive trian at 125 volts for 1 second and then halts the drive train.
    Hardware : 
        - frontRightMotor
        - frontLeftMotor
        - rearRightMotor
        - rearLeftMotor
*/
void shoveIn();

//? Odometry Functions
void calibrateWheelAndCenterDistance();
double getDeltaTheta(double deltaCurrent, double deltaPrevious);
void updateGlobalLocation();
void recalibratePosition();
void displayOdomParamters();

//? Command Class

/*
    Class Name : autonCommandType
    Author : Veera Unnam (Jo)
    Description : This class holds enumrated values regarding all the actions that can be performed during autonomous. This enum is to facilitate
    a future project where a Graphical User Interface (GUI) can be used to plan our auton routine
*/
enum autonCommandType{
    move = 0,
    rotate = 1, 
    catapult = 2, 
    wingIn = 3, 
    wingOut = 4, 
    intake = 6, 
    outtake = 7, 
    stopIntake = 8, 
    shoveCommand = 9
};

/*
    Class Name : autonCommand
    Author : Veera Unnam (Jo)
    Description : This class is a part of an API being programmed in order to interface between the GUI autonomous planner, which is written
    in Dart, with the Robot Program, which is written in C++. The autonCommand has to do with implementing the auton tasks that were set with
    the GUI planner.
    Attributes : 
        - type : This variable, which holds an enum, stores what kind of autonCommand that specific instance of the calss has to perform
        - parameter : This variable holds any parameters that have to be 
*/
class autonCommand{
    public : 
        autonCommandType type;
        double parameter = 0;
        autonCommand(autonCommandType typeTemp, double parameterTemp = 0){
            type = typeTemp;
            parameter = parameterTemp;            
        }
        void runCommand(){
            switch(type){
                /*case move:
                    moveForward(parameter);
                    break;
                case rotate:
                    rotateTo(parameter);
                    break;*/
                case intake:
                    runIntake(parameter);
                    break;
                case outtake:
                    runOuttake(parameter);
                    break;
                case stopIntake:
                    haltIntakeOutake();
                    break;
                case shoveCommand:
                    shoveIn();
                    break;
            }
        }
};
//? Command Decryption Commands
std::vector<std::string> split();
autonCommand decodeString();
std::vector<autonCommand> processEncodedString();
//? Auton Algorithms
void leftSideAutonomous();
void rightSideAutonomous();
void skillsAutonomous();

