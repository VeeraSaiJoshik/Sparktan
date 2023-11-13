#include "main.h"

using namespace pros;

void primaryOperatorControl(void* param){
    ButtonClass switchDriveTrainButton = ButtonClass(E_CONTROLLER_DIGITAL_A);
    while(true){
        if(switchDriveTrainButton.checkIfButtonPressed()){
            if(driveTrainMode == Arcade){
                driveTrainMode = Tank;
            }else{
                driveTrainMode = Arcade;
            }
        }
        driveTrainFunction();
        delay(20);
    }
}
void secondaryOperatorControl(void* param){
    while (true){
        delay(20);
    }
}
void tertiaryOperatorControl(void* param){
    while(true){
        delay(20);
    }
}