#pragma once
#include "main.h"
//^ ENUMs declarations
extern pros::Controller brain;
enum JoystickSide{
    leftSideJoyStick = 0, 
    rightSideJoyStick = 1
};
enum DriveTrainMode{
    Tank = 0, 
    Arcade = 1
};

class JoystickValues{
    public : 
        double xValue;
        double yValue;
        bool joyStickUsed(){
            return (xValue != 0 || yValue != 0);
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
        bool buttonPressedPreviously = false;
        ButtonClass(pros::controller_digital_e_t buttonTemp){
            button = buttonTemp;
        }
        bool checkIfButtonPressed(){
            bool currentlyPressed = brain.get_digital(button);
            bool buttonPressed = false;
            if(buttonPressedPreviously && currentlyPressed == false) buttonPressed = true;
            buttonPressedPreviously = currentlyPressed;
            return buttonPressed;
        }
};

class OdometryPod{
	public :
		double previousTicks = 0;
		double wheelRadius = 0;
		double distanceToCenter = 0;
        double dt;
		pros::ADIEncoder encoder;
		OdometryPod(int portTop, int portBototm, bool reverse, int wheelRadiusTemp = 0, int distanceToCenterTemp = 0) : encoder(portTop, portBototm, reverse) {
			wheelRadius = wheelRadiusTemp;
			distanceToCenter = distanceToCenterTemp;
		}
		// Setter Functions
		void setDistanceToCenter(double dtctemp){	
			distanceToCenter = dtctemp;
		}
		void setWheelRadiusValue(double wheelRadiusTemp){
			wheelRadius = wheelRadiusTemp;
		}
		// getter functions
		double getDeltaTicks(){
			double deltaTicks = encoder.get_value() - previousTicks;
			previousTicks = encoder.get_value();
			return deltaTicks;
		}
		double getDistanceTraveled() {
            double deltaTheta = getDeltaTicks() * (3.141592653/180);
            dt = deltaTheta;
            return deltaTheta * wheelRadius;
		}
        int getTicks(){
            return encoder.get_value();
        }
};

//^ Variable Declarations
//& General Variables
extern double PI;

extern pros::ADIDigitalIn intakeBumperSwitch;
extern bool catapultRunning;
extern std::string autonCommandStringEncoded;
extern pros::IMU imuController;
extern ButtonClass rachetButton;
extern ButtonClass lockLiftButton;
extern int armTotalTicks;

//& Drivetrain Variables
extern pros::Motor frontRightMotor;
extern pros::Motor frontLeftMotor;
extern pros::Motor rearRightMotor;
extern pros::Motor rearLeftMotor;
extern DriveTrainMode driveTrainMode;
extern ButtonClass switchDriveTrainButton;

//& Other Motor Variables
extern pros::Motor intakeMotor;
extern pros::Motor catapultMotor;
extern pros::Motor liftMotor;
extern pros::Motor rachetMotor;
extern pros::Motor puncherMotor;
//& Odometry Variables
//* Global Location Variable
extern double globalX;
extern double globalY;
//* Tracker Variables
extern double thetaPrevious;
//* constant variables
extern double degToRad;
//* sensor variables
extern OdometryPod rightPod;
extern OdometryPod leftPod;
extern OdometryPod backPod;

extern bool wingsOut;