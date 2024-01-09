#include "main.h"
//? Auton Preset Moves
void moveForward(double inches){
    moveRobotBy(inches);
}
void rotateTo(double degrees){
    rotateRobotTo(degrees);
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
void calibrateWheelAndCenterDistance(){
    // getting initial data
    double initialTheta = imuController.get_heading() * degToRad;
    rotateRobotBy(180);
    // getting final data
    int deltaRightPod = rightPod.getDeltaTicks();
    int deltaLeftPod = leftPod.getDeltaTicks();
    int deltaBackPod = backPod.getDeltaTicks();
    double finalTheta = imuController.get_heading() * degToRad;
    double deltaTheta = 0;
    if(finalTheta < initialTheta) deltaTheta = 2 * PI - initialTheta + finalTheta;
    else deltaTheta = finalTheta - initialTheta;
    // determing the distances
    rightPod.distanceToCenter = rightPod.getDistanceTraveled()/deltaTheta;
    leftPod.distanceToCenter = leftPod.getDistanceTraveled()/deltaTheta;
    backPod.distanceToCenter = backPod.getDistanceTraveled()/deltaTheta;
    // displaying data
    pros::lcd::set_text(0, "Right -> Center Distance : " + std::to_string(rightPod.distanceToCenter));
    pros::lcd::set_text(0, "Left -> Center Distance : " + std::to_string(leftPod.distanceToCenter));
    pros::lcd::set_text(0, "Back -> Center Distance : " + std::to_string(backPod.distanceToCenter));
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
void rightSideAutonomous(){
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


}
void skillsAutonomous(){
    
}