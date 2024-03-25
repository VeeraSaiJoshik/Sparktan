#include "main.h"
#include "fstream"
// Jhon was here
void initialize() {
    // calibrating the screen    
    pros::lcd::initialize();
    // declaring all the variable values and brake values
    liftMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
   // catapultMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
    rachetMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
    frontRightMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    frontLeftMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    rearRightMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    rearLeftMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    intakeMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
    //wings.set_value(false);
    // calibrating the Intertial Measurment Unit
    checkOverHeating();
    imuController.set_data_rate(10);
	imuController.reset();
	pros::delay(200);
	while(imuController.is_calibrating()){
		pros::lcd::set_text(1, "IMU is Calibrating : DO NOT TOUCH");
		pros::delay(100);
	}
    pros::lcd::set_text(1, "YEAH THIS IS DONE");
}
void disabled() {}

void competition_initialize() {}
pros::ADIDigitalOut pneum('F');
void pt4autn(){
    expansion();
    runIntake(1000, 600);
    moveRobotByPID(35);
    rotateRobotBy(45);
    runOuttake(400, 400);
    rotateRobotBy(-1 * abs(90 + 55));
    moveRobotByPID(20);
    runIntake(1000, 600);
    moveRobotByPID(-7);
    rotateRobotBy(140);
    runOuttake(400, 400);
    rotateRobotBy(-90);
    moveRobotByPID(20);
    runIntake(1000, 600);
    rotateRobotTo(80);
    pneum.set_value(true);
    runOuttake(400, 200);
    moveDriveTrain(600);
    pros::delay(700);
    brakeDriveTrain();
    moveRobotByPID(-5);
    runOuttake(400, 400);

    /*
    moveDriveTrain(600);
    pros::delay(300);
    brakeDriveTrain();
    */
}
void skills(){
    expansion();
    liftMotor.move_voltage(12000);
    pros::delay(700);
    liftMotor.brake();
    puncherMotor.move_voltage(-12000);
    //rotateRobotBy(-45);
    
}
void autonomous() {    
    //skills();
    pt4autn();
    /*moveRobotByPID(59);
    runIntake(1000, 600);
    rotateRobotBy(90 + 45);
    pneum.set_value(true);
    moveRobotByPID(8);
    runOuttake(300, 600);
    moveDriveTrain(600);
    pros::delay(700);
    brakeDriveTrain();
    pneum.set_value(false);
    pros::delay(300);
    moveRobotByPID(-5);
    rotateRobotBy((90 + 55));
    moveRobotByPID(17);
    runIntake(1000, 600);*/
    /*
    moveRobotByPID(30);
    
    rotateRobotBy(37);
    runOuttake(300, 400);
    rotateRobotBy(-87);
    moveRobotByPID(28);
    runIntake(1000, 600);
    rotateRobotTo(90);
    moveRobotByPID(15);
    runOuttake(350, 600);
    moveDriveTrain(600);
    pros::delay(400);
    brakeDriveTrain();
    moveRobotByPID(-20);
    rotateRobotTo(180+45);
    //moveRobotByPID(16);
    runIntake(1000, 600);
    rotateRobotBy(-90);
    moveRobotByPID(30);
    runOuttake(350, 600);
    rotateRobotTo(270);*/
}
/*

*/

void autonRoute(){
    expansion();
    moveRobotByPID(58);
    runIntake(1000, 600);
    rotateRobotBy(135);
    moveRobotByPID(25);
    runOuttake(300, 400);
    moveDriveTrain(600);
    pros::delay(500);
    brakeDriveTrain();
    moveRobotByPID(-5);
    rotateRobotBy(135);

}
void opcontrol() {
   pros::lcd::set_text(6, "OP COntrol has started");
   pros::Task primary(primaryOperatorControl);
   pros::Task secondary(secondaryOperatorControl);
   
   //pros::Task odometry(odometryThread);
   //rotateRobotTo(90);
   /*odomGUI gui = odomGUI();
   lv_mem_init();
   while(true){
    gui.draw();
    pros::delay(1000);
   }*/
}