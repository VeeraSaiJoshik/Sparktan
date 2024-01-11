#include "main.h"

using namespace pros;

void primaryOperatorControl(void* param){
    rachetMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
    while(true){
        if(switchDriveTrainButton.checkIfButtonPressed()){
            if(driveTrainMode == Arcade){
                driveTrainMode = Tank;
            }else{
                driveTrainMode = Arcade;
            }
            moveRobotBy(10);
            //rotateRobotTo(180);
            //moveRobotBy(5);
            //intakeMotor = 50;
        }
        pros::lcd::set_text(5, std::to_string(rightPod.getDeltaTicks()));
        pros::lcd::set_text(6, std::to_string(backPod.getDeltaTicks()));
        
        driveTrainFunction();
        intakeOperation();
        liftOperation();
        delay(20);
    }
}
void secondaryOperatorControl(void* param){
    while (true){
        catapultOperation();
        
        delay(20);
    }
}