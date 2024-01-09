#include "main.h"
#include "chrono"
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
    if(brain.get_digital(DIGITAL_RIGHT)){
        liftMotor.move_velocity(-100);
    }else if(brain.get_digital(DIGITAL_LEFT)){
        liftMotor.move_velocity(100);
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
    if(matchLoadButton.checkIfButtonPressed()){
        if(catapultRunning){
            catapultMotor.brake();
            catapultRunning = false;
        }else{
            catapultMotor = 120;
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
void expansion(){
    int targetTick = liftMotor.get_position() - 4000;
    liftMotor.move_relative(-1 * 4000 , -200);
    int time = 0;
    while(((liftMotor.get_position() <= targetTick + armTotalTicks/180) && (liftMotor.get_position() >= targetTick  - armTotalTicks/180)) == false){
        if(time >= 2500){
            break;
        }
        pros::delay(20);
        time += 20;
    }
    pros::lcd::set_text(0, "Actually im done");
    runIntake(600);
    pros::lcd::set_text(0, "LIFT MOTOR DONE");

}