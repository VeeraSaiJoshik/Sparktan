#include "main.h"
#include "chrono"
bool thing = false;
    bool thing2 = true;
void wingOperation(){
    
    /*
    
    */
}
void intakeOperation(){
    if(brain.get_digital(DIGITAL_R1)){
        intakeMotor.move_voltage(12000);//Intake
    }else if(brain.get_digital(DIGITAL_R2)){
        intakeMotor.move_velocity(-600);//Outtake
    }else if(brain.get_digital_new_press(DIGITAL_L1)){
        runIntake(500, 600);
    }
    else{
        intakeMotor.move_velocity(0);
    }
}
void liftOperation(){
    if(brain.get_digital(DIGITAL_RIGHT)){
        liftMotor.move_voltage(-12000);
    }else if(brain.get_digital(DIGITAL_LEFT)){
        liftMotor.move_velocity(12000);
    }else{
        liftMotor.move_velocity(0);
    }
    if(lockLiftButton.checkIfButtonPressed()){
        rachetMotor = 125;
        pros::delay(20);
        rachetMotor = 0;
    }else if(brain.get_digital(DIGITAL_UP)){
        rachetMotor = -125;
    }else{
        rachetMotor = 0;
    }
}
void catapultOperation(){
    if(rachetButton.checkIfButtonPressed()){
        if(catapultRunning){
        //    catapultMotor.brake();
            catapultRunning = false;
        }else{
         //   catapultMotor = 120;
            catapultRunning = true;
        }
    }
}
void moveLiftMotor(int move){
    int targetTick = liftMotor.get_position() + move;
    if(move < 0){
        liftMotor.move_relative(move , -200);
    }else{
        liftMotor.move_relative(move , 200);
    }
    while(((liftMotor.get_position() <= targetTick + armTotalTicks/180) && (liftMotor.get_position() >= targetTick  - armTotalTicks/180)) == false){
        pros::delay(20);    
    }
}

void rachetOperation(){
    if(rachetButton.checkIfButtonPressed()){
        puncherMotor = -200;
    }else{
        puncherMotor.brake();
    }
}
void expansion(){
    //liftMotor.move_absolute(-400, -600);
    // Pump out wing
    //while(fabs(liftMotor.get_position() + 400) > 5){
      //  pros::delay(10);
    //}
    liftMotor.move_voltage(-12000);
    pros::delay(300);
    liftMotor.brake();
    // Pump in wing
}