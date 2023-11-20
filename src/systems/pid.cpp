#include "main.h"
//^ General Functions
double clampMotorVoltage(double voltage){
    return voltage > 125 ? 125 : voltage < -125 ? -125 : voltage;
}
double normalizeAngle(double angle){
    return angle > 360 ? angle - 360 : angle < 360 ? 360 + angle : angle;
}
//* Rotational PID Code
//^ Angular Error Functions
double getAngularError(double currentAngle, double targetAngle){
    double distanceClockWise = getErrorClockwise(currentAngle, targetAngle);
    double distanceCounterClockWise = getErrorCounterclockwise(currentAngle, targetAngle);
    if(distanceClockWise < distanceCounterClockWise){
        return distanceClockWise;
    }
    return distanceCounterClockWise;
}
double getErrorClockwise(double currentAngle, double targetAngle){
    double distanceClockWise = 0;
    if(currentAngle > targetAngle){
        distanceClockWise = (360 - currentAngle) + targetAngle;
    }else{
        distanceClockWise = targetAngle - currentAngle;
    }
    return distanceClockWise;
}
double getErrorCounterclockwise(double currentAngle, double targetAngle){
    // TODO : Check if this function returns positive or negative value for counter clockwise turns
    double distanceCounterclockWise = 0;
    if(currentAngle < targetAngle){
        distanceCounterclockWise = currentAngle + (360 - targetAngle);
    }else{
        distanceCounterclockWise = currentAngle - targetAngle;
    }
    return -1 * distanceCounterclockWise;
}
//^ PID Function
void rotateRobotTo(double targetAngle){
    float Kp = 1.7;
    float Ki = 0.04;
    float Kd = 0.08;
    float error;
    float integral = 0;
    double derivative;
    int throttleSpeed;
    bool calculateIntegral = true;
    float curPosition = imuController.get_heading();
    float prevError = getAngularError(curPosition, targetAngle);
    pros::lcd::set_text(1, "PID is working");
    while(true){
        curPosition = imuController.get_heading();
        
        error = getAngularError(curPosition, targetAngle);
        derivative = error - prevError;
        if(calculateIntegral) integral += error;
        
        if(error < 2 || error > -2) break;

        throttleSpeed = Kp * error + Kd * derivative + Ki * integral;
        rotateDriveTrain(clampMotorVoltage(throttleSpeed));
        
        calculateIntegral = ((throttleSpeed != clampMotorVoltage(throttleSpeed)) && ((throttleSpeed < 0 && error < 0) || (throttleSpeed > 0 && error > 0)));
        pros::delay(20);
    }
}
void rotateRobotBy(double targetDegrees){
    rotateRobotTo(normalizeAngle(targetDegrees));
}
//^ Autotune Functions
void autoTunePID(){

}
void robotRotationModel(){

}
void gatherRotationalModelDataPoints(){
    //TODO : Write code to check angular displacement per second given the motor voltage from 0 - 125 with 2 voltage increments
}