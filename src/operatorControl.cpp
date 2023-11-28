#include "main.h"

using namespace pros;

void primaryOperatorControl(void* param){
    while(true){
        if(switchDriveTrainButton.checkIfButtonPressed()){
            if(driveTrainMode == Arcade){
                driveTrainMode = Tank;
            }else{
                driveTrainMode = Arcade;
            }
        }
        driveTrainFunction();
        intakeOperation();
        wingOperation();
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