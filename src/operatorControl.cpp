#include "main.h"

using namespace pros;

void primaryOperatorControl(void* param){
    pros::ADIDigitalOut pneum('F');
    rachetMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
    expansion();
    while(true){
        pros::lcd::set_text(3, std::to_string(rightPod.getDistanceTraveled()));
        
        if(brain.get_digital_new_press(DIGITAL_L2)){
            if(wingsOut){
                pneum.set_value(false);
                wingsOut = false;
            }else{
                pneum.set_value(true);
                wingsOut = true;
            }
        }
        if(brain.get_digital(DIGITAL_B)){
            puncherMotor.move_voltage(12000);
        }else{
            puncherMotor.brake();
        }
        if(switchDriveTrainButton.checkIfButtonPressed()){
            if(driveTrainMode == Arcade){
                driveTrainMode = Tank;
            }else{
                driveTrainMode = Arcade;
            }
        }
        driveTrainFunction();
        
        liftOperation();
        delay(20);
    }
}
void dataLog(){
    FILE* dataFile = fopen("/usd/odometry.txt", "w");
    while(true){
        fprintf(dataFile, "%f,%f\n", globalX, globalY);
        if(switchDriveTrainButton.checkIfButtonPressed())break;
        delay(20);
    }
    fclose(dataFile);
}
void secondaryOperatorControl(void* param){
    while (true){
        intakeOperation();
        delay(20);
    }
}