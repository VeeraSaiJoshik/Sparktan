#include "main.h"
#include "math.h"
//? Auton Preset Moves
void moveForward(double inches){
    moveRobotBy(inches);
}
void rotateTo(double degrees){
    rotateRobotTo(degrees);
}
void moveTo(double x, double y){
    
}
void runIntake(int milliseconds, int velocity = 600){
    intakeMotor.move_velocity(velocity);
    int time = 0;
    int continous = 0;
    while(time <= milliseconds){
        if(intakeBumperSwitch.get_value()){
            continous++;
        }else{
            continous = 0;
        }

        if(continous == 20){
            intakeMotor = 0;
            break;
        }
        pros::delay(20);
        time += 20;
    }
    intakeMotor.move_velocity(0);
}
void runOuttake(int milliseconds, int voltage){
    intakeMotor.move_velocity(-voltage);
    if(milliseconds != -1){
        pros::delay(milliseconds);
        intakeMotor.move_velocity(0);
    }
}
void haltIntakeOutake(){
    intakeMotor.move_velocity(0);
}
void shoveIn(){
    moveDriveTrain(100);
    pros::delay(1000);
    moveDriveTrain(0);
}
//? Odometry Functions
double getDeltaTheta(double thetaCurrent, double thetaPrevious){
    double deltaThetaClockwise, deltaThetaCounterClockwise;
    if(thetaCurrent < thetaPrevious){
        deltaThetaClockwise = 2 * PI - thetaPrevious + thetaCurrent;
        deltaThetaCounterClockwise = -1 * (thetaPrevious - thetaCurrent);
    }else{
        deltaThetaClockwise = thetaCurrent - thetaPrevious;
        deltaThetaCounterClockwise = (2 * PI - thetaCurrent + thetaCurrent) * -1;
    }
    if(deltaThetaClockwise < fabs(deltaThetaCounterClockwise)) return deltaThetaClockwise;
    return deltaThetaCounterClockwise;
}
void globalizePosition(){
    
}
void calibrateWheelAndCenterDistance(){
    // getting initial data
    double initialTheta = imuController.get_heading() * degToRad;
    rotateRobotBy(180);
    // getting final data
    double finalTheta = imuController.get_heading() * degToRad;
    double deltaTheta = 0;
    if(finalTheta < initialTheta) deltaTheta = 2 * PI - initialTheta + finalTheta;
    else deltaTheta = finalTheta - initialTheta;
    // determing the distances
    double rightDistance = rightPod.getDistanceTraveled();
    rightPod.distanceToCenter = rightDistance/deltaTheta;
   // leftPod.distanceToCenter = leftPod.getDistanceTraveled()/deltaTheta;
    backPod.distanceToCenter = backPod.getDistanceTraveled()/deltaTheta;
    // displaying data
    pros::lcd::set_text(0, "Right -> Center Distance : " + std::to_string(rightPod.distanceToCenter));
    pros::lcd::set_text(1, "Back -> Center Distance : " + std::to_string(backPod.distanceToCenter));
    pros::lcd::set_text(2, "Right Distance : " + std::to_string(rightDistance));
    pros::lcd::set_text(3, "Delta THeta : " + std::to_string(rightPod.dt));
}
void updateGlobalVariables(){
    double thetaCurrent = imuController.get_heading() * degToRad;
    long double deltaX = 0;
    long double deltaY = 0;
    // calculate delta theta right pod
    double deltaTheta = getDeltaTheta(thetaCurrent, thetaPrevious);
    if(fabs(deltaTheta) != 0){
        // performing exact integration on right pod
        double distanceTraveledRightPod =  (rightPod.getDistanceTraveled()/deltaTheta + rightPod.distanceToCenter);
        deltaX = -1 * distanceTraveledRightPod * (sin(thetaCurrent) - sin(thetaPrevious));
        deltaY = distanceTraveledRightPod * (cos(thetaCurrent) - cos(thetaPrevious));
    }else{
        // performing range-kuta integration on right pod
        deltaX = rightPod.getDistanceTraveled() * cos(thetaCurrent);
        deltaY = rightPod.getDistanceTraveled() * sin(thetaCurrent);
    }
    // calculate delta theta left pod
    if(fabs(deltaTheta) != 0){
        // performing exact integration on back pod
        double distanceTraveledRightPod =  (backPod.getDistanceTraveled()/deltaTheta + backPod.distanceToCenter);
        deltaY += distanceTraveledRightPod * (sin(fmod((thetaCurrent + PI/2),(2 * PI))) - sin(fmod((thetaPrevious + PI/2),(2 * PI))));
        deltaX += distanceTraveledRightPod * (cos(fmod((thetaCurrent + PI/2),(2 * PI))) - cos(fmod((thetaPrevious + PI/2),(2 * PI))));
    }else{
        // performing range-kuta integration on back pod
        deltaX += backPod.getDistanceTraveled() * cos(thetaCurrent);
        deltaY += backPod.getDistanceTraveled() * sin(thetaCurrent);
    }
    // updating global variables
    globalX += deltaX;
    globalY += deltaY;
    thetaPrevious = thetaCurrent;
}
void recalibratePosition(){

}
void displayOdomParamters(){
    pros::lcd::set_text(0, "X Position : " + std::to_string(globalX));
    pros::lcd::set_text(1, "Y Position : " + std::to_string(globalY));
}
void odometryThread(void *param){
    while(true){
        updateGlobalVariables();
        displayOdomParamters();
        pros::delay(20);
    }
}
//? Auton Routines
void leftSideAutonomous(){
    expansion();
    moveForward(45);
    pros::delay(100);
    rotateTo(270);   
    runOuttake(400);
    rotateRobotBy(180);
    moveDriveTrain(-100);
    pros::delay(300);
    brakeDriveTrain();
    moveForward(5);
    rotateRobotBy(-90);
    moveForward(10);
    rotateRobotBy(-90);
    moveDriveTrain(-70);
    pros::delay(3500);
    brakeDriveTrain();
    moveDriveTrain(100);
    pros::delay(500);
    brakeDriveTrain();
    moveDriveTrain(-100);
    pros::delay(500);
    brakeDriveTrain();
}
/*void rightSideAutonomous(){
    expansion();
    moveForward(45);
    pros::delay(100);
    rotateTo(90);   
    runOuttake(400);
    pros::delay(100);
    rotateTo(330);   
    moveForward(8);
    runIntake(500);
    rotateTo(90);
    runOuttake(500);
    rotateRobotBy(180);
    moveDriveTrain(-100);
    pros::delay(400);
    brakeDriveTrain();
}*/

void rightSideAutonomous(){
    expansion();
    //! Phase 1 : 
    moveRobotByPID(45);
    pros::delay(300);
    rotateRobotTo(70);
    pros::delay(300);
    intakeMotor.move_velocity(-300);
    pros::delay(300);
    intakeMotor.move_velocity(0);
    pros::delay(300);
    rotateRobotTo(315);
    moveRobotByPID(8);
    intakeMotor.move_velocity(300);
    pros::delay(500);
    intakeMotor.move_velocity(0);
    pros::delay(500);
    rotateRobotTo(0);
    moveRobotByPID(6);
    rotateRobotTo(90);
    runOuttake(400);
    
    rotateRobotTo(280);
    
    moveDriveTrain(-80);
    pros::delay(500);
    brakeDriveTrain();

    moveDriveTrain(50);
    pros::delay(200);
    brakeDriveTrain();
    rotateRobotTo(270);
    moveRobotByPID(26);
    intakeMotor.move_velocity(200);
    pros::delay(200);
    intakeMotor.move_velocity(0);
    rotateRobotTo(90);
    moveRobotByPID(14);
    intakeMotor.move_velocity(-300);
    pros::delay(400);
    intakeMotor.move_velocity(0);
    moveRobotByPID(18);
    moveDriveTrain(-80);
    pros::delay(300);
    brakeDriveTrain();
   
   brakeDriveTrain();
}
void skillsAutonomousRobot2(){
    moveRobotByPID(45);
    rotateRobotTo(55);
    pros::delay(200);
    runOuttake(400);
    pros::delay(200);
    rotateRobotTo(321);
    moveRobotByPID(8);
    pros::delay(200);
    runIntake(400);
    pros::delay(200);
    rotateRobotTo(89);
    pros::delay(200);
    runOuttake(400);
    rotateRobotTo(275);
    moveRobotByPID(25);
    pros::delay(200);
    runIntake(400);
    rotateRobotTo(89);
    pros::delay(200);
    runOuttake(400);
    rotateRobotTo(193);
    moveRobotByPID(13);
    pros::delay(200);
    runIntake(400);
    rotateRobotTo(69);
    moveRobotByPID(23);
    pros::delay(200);
    runOuttake(400);
    rotateRobotTo(76);
    moveRobotByPID(8);

}

    /*rotateRobotTo(359.88981594445704);
moveRobotByPID(41);
rotateRobotTo(50);
runOuttake(400);
rotateRobotTo(326.76828893202065);
moveRobotByPID(5);
pros::delay(200);
runIntake(300);
pros::delay(200);
moveRobotByPID(10);
rotateRobotTo(89);
pros::delay(200);
runOuttake(400);
moveDriveTrain(100);
pros::delay(500);
brakeDriveTrain();*/

 /*
    //! Phase 2 : 
    
    pros::delay(300);
    
    //! Phase 3
    
    // push
    moveDriveTrain(-80);
    pros::delay(400);
    brakeDriveTrain();
    // done push
    //! Phase 4
    
    rotateRobotTo(260);
    moveRobotByPID(18);
    pros::delay(300);
    runIntake(200);
    pros::delay(300);
    rotateRobotTo(86);
    runOuttake(500);
    rotateRobotTo(260);
    
    */
void auton6point(){
    
}