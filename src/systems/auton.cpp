#include "main.h"
void moveForward(double inches){
    moveRobotBy(inches);
}
void rotateTo(double degrees){
    rotateRobotTo(degrees);
}
void shootCatapult(){
    loadCatapult();
    shootCatapult();
}
void pullWingsIn(){
    wings.set_value(false);
}
void pullWingsOut(){
    wings.set_value(true);
}
void runIntake(int milliseconds){
    intakeMotor.move_velocity(600);
    if(milliseconds != -1){
        pros::delay(milliseconds);
        intakeMotor.move_velocity(0);
    }
}
void runOuttake(int milliseconds){
    intakeMotor.move_velocity(-600);
    if(milliseconds != -1){
        pros::delay(milliseconds);
        intakeMotor.move_velocity(0);
    }
}
void haltIntakeOutake(){
    intakeMotor.move_velocity(0);
}
void shove(){
    shoveIn();
}