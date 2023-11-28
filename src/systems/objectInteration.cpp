#include "main.h"
void intakeOperation(){
    if(brain.get_digital(DIGITAL_R1)){
        intakeMotor.move_velocity(600);//Intake
    }else if(brain.get_digital(DIGITAL_R2)){
        intakeMotor.move_velocity(-600);//Outtake
    }else{
        intakeMotor.move_velocity(0);
    }
}
void liftOperation(){
    if(brain.get_digital(DIGITAL_X)){
        liftMotor.move_velocity(100);
    }else{
        liftMotor.brake();
    }
}
void loadCatapult(){
	catapultMotor = 100;
	while(true){
  		std::cout << "Sensor Reading:" << catapultLimitSwitch.get_value();
		if(catapultLimitSwitch.get_value() == 1) break;
		pros::delay(20);
	}
	catapultMotor = 0;
}
void shootCatapult(){
	catapultMotor = 120;
	pros::delay(40);
	catapultMotor = 0;	
}
void catapultOperation(){
    if(matchLoadButton.checkIfButtonPressed()){
        if(catapultRunning){
            catapultMotor = 125;
            catapultRunning = false;
        }else{
            catapultMotor.brake();
            catapultRunning = true;
        }
    }
    else if(brain.get_digital(DIGITAL_L1)){
        loadCatapult();
    }else if(brain.get_digital(DIGITAL_L2)){
        shootCatapult();
    }
}
void wingOperation(){
    if(extendWings.checkIfButtonPressed()){
        if(wingsExtended){
            wings.set_value(false);
        }else{
            wings.set_value(true);
        }
    }
}