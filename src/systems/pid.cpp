#include "main.h"
#include "iostream"
#include "fstream"
//^ General Functions
double clampMotorVoltage(double voltage){
    return voltage > 125 ? 125 : voltage < -125 ? -125 : voltage;
}
double clampMotorSpeed(int speed){
    return speed > 200 ? 200 : speed < -200 ? -200 : speed;
}
double normalizeAngle(double angle){
    return angle > 360 ? angle - 360 : angle < 360 ? 360 + angle : angle;
}
//* Rotational PID Code
//^ Angular Error Functions
double getAngularError(double currentAngle, double targetAngle){
    double distanceClockWise = getClockwiseError(currentAngle, targetAngle);
    double distanceCounterClockWise = getCounterClockwiseError(currentAngle, targetAngle);
    if(distanceClockWise < distanceCounterClockWise){
        return distanceClockWise;
    }
    return distanceCounterClockWise;
}
double getClockwiseError(double currentAngle, double targetAngle){
    double distanceClockWise = 0;
    if(currentAngle > targetAngle){
        distanceClockWise = (360 - currentAngle) + targetAngle;
    }else{
        distanceClockWise = targetAngle - currentAngle;
    }
    return distanceClockWise;
}
double getCounterClockwiseError(double currentAngle, double targetAngle){
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
//! Rotational
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
        rotateDriveTrainWithVelocity(clampMotorSpeed(throttleSpeed));
        
        calculateIntegral = ((throttleSpeed == clampMotorVoltage(throttleSpeed)) && ((throttleSpeed < 0 && error < 0) || (throttleSpeed > 0 && error > 0)));
        prevError = error;
        pros::delay(20);
    }
}
void rotateRobotBy(double targetDegrees){
    rotateRobotTo(normalizeAngle(imuController.get_heading() + targetDegrees));
}
//! Movment
void moveRobotBy(double inches){
    
}
void shove(){

}
//^ Autotune Functions
void autoTunePID(){

}

void gatherRotationalModelDataPoints(){
    int currentVoltage = 0;
    double previousAngle = 0;
    double currentAngle = 0;
    double deltaAngle = 0;
    std::fstream dataLog;
    dataLog.open("/usd/PIDAutotuneData.csv");
    while(true){
        if(currentVoltage > 120000) break;
        if(getDriveTrainVoltage() == currentVoltage){
            previousAngle = imuController.get_heading();
            pros::delay(1000);
            currentAngle = imuController.get_heading();
            deltaAngle = currentAngle - previousAngle;
            dataLog << std::to_string(currentVoltage) << "," << std::to_string(deltaAngle) << "\n"; // <- Data logging techniques
            currentVoltage = currentVoltage + 1000;
            rotateDriveTrainAccurate(currentVoltage);
        }
    }
}
//^ Measurement Functions
void measureMotorRPMChange(int targetRPM){
    std::fstream dataLog;
    dataLog.open("/usd/MotorChangeData.csv");
    int time = 0;
    dataLog << "Target RPM : " << targetRPM << std::endl;
    rotateDriveTrainWithVelocity(targetRPM);
    while(true){
        double averageVelocity = getDriveTrainVelocity();
        if(averageVelocity == targetRPM){
            break;
        }
        dataLog << time << "," << averageVelocity << "," << rearLeftMotor.get_actual_velocity() << "," << rearRightMotor.get_actual_velocity() << "," << frontLeftMotor.get_actual_velocity() << "," << frontRightMotor.get_actual_velocity() << std::endl;
        time = time + 2;
        pros::delay(2);
    }
}
void measureAngularChangeRPM(int minimumRPM, int maximumRPM){
    float deltaAnglePrevious = 0;
    float deltaAngle = 0;
    std::fstream dataLog;
    dataLog.open("/usd/AngularChangeRPM.csv");
    for(int RPM = minimumRPM; RPM <= maximumRPM; RPM++){
        rotateDriveTrainWithVelocity(RPM);
        // wait till the RPM is actually reached
        while(getDriveTrainVelocity() != RPM) pros::delay(2);
        // After the RPM is reached run the program for 1 second and log the delta angle
        deltaAnglePrevious = imuController.get_heading();
        pros::delay(1000);
        deltaAngle = imuController.get_heading() - deltaAnglePrevious;
        // repeat
        dataLog << RPM << "," << deltaAngle << std::endl;
        pros::delay(10);
    }
}
