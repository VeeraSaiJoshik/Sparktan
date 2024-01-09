#include "main.h"
#include "fstream"

void initialize() {
    // calibrating the screen    
    /*
    // declaring all the variable values and brake values
    liftMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
    catapultMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
    rachetMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
    frontRightMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    frontLeftMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    rearRightMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    rearLeftMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    //wings.set_value(false);
    // calibrating the Intertial Measurment Unit
    imuController.set_data_rate(10);
	imuController.reset();
	pros::delay(200);
	while(imuController.is_calibrating()){
		pros::lcd::set_text(1, "IMU is Calibrating : DO NOT TOUCH");
		pros::delay(100);
	}
    pros::lcd::set_text(1, "YEAH THIS IS DONE");*/
    
}
void disabled() {}

void competition_initialize() {}

void autonomous() {
    rachetMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
    rightSideAutonomous();
    
}
/*

*/

void opcontrol() {
   // pros::lcd::set_text(6, "OP COntrol has started");
   // pros::Task primary(primaryOperatorControl);
   // pros::Task secondary(secondaryOperatorControl);
   //rotateRobotTo(90);
   odomGUI gui = odomGUI();
   lv_mem_init();
   while(true){
    gui.draw();
    pros::delay(1000);
   }
}