#pragma once
#include "pros/motors.h"
//^ ENUMs declarations
enum JoystickSide{
    leftSideJoyStick = 0, 
    rightSideJoyStick = 1
};
enum DriveTrainMode{
    Tank = 0, 
    Arcade = 1
};

//^ Variable Declarations
//& General Variables
extern double PI;
extern pros::Controller brain;
//& Drivetrain Variables
extern pros::Motor frontRightMotor;
extern pros::Motor frontLeftMotor;
extern pros::Motor rearRightMotor;
extern pros::Motor rearLeftMotor;
extern DriveTrainMode driveTrainMode;

//^ Class Declarations
class JoystickValues{
    public : 
        double xValue;
        double yValue;
        bool joyStickUsed(){
            return (xValue == 0 && yValue == 0);
        }
        JoystickValues(JoystickSide joyStick){
            if(joyStick == leftSideJoyStick){
                xValue = brain.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
                yValue = brain.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
            }else{
                xValue = brain.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
                yValue = brain.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
            }
        }
};
class ButtonClass{
    public : 
        pros::controller_digital_e_t button;
        bool currentlyPressed = false;
        bool buttonPressed = false;
        ButtonClass(pros::controller_digital_e_t buttonTemp){
            button = buttonTemp;
        }
        bool checkIfButtonPressed(){
            if(currentlyPressed != brain.get_digital(button)){
                currentlyPressed = brain.get_digital(button);
                buttonPressed = currentlyPressed == false;
            }else{
                currentlyPressed = brain.get_digital(button);
            }
            return currentlyPressed;
        }
};