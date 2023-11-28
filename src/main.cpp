#include "main.h"

void initialize() {
    // calibrating the screen
    pros::lcd::initialize();
    // declaring all the variable values and brake values
    liftMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
    catapultMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
    wings.set_value(false);
    // calibrating the Intertial Measurment Unit
    imuController.set_data_rate(10);
	imuController.reset();
	pros::delay(200);
	while(false){//imuController.is_calibrating()){
		pros::lcd::set_text(1, "IMU is Calibrating : DO NOT TOUCH");
		pros::delay(100);
	}
}
void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
    pros::Task primary(primaryOperatorControl);
    pros::Task secondary(secondaryOperatorControl);
}