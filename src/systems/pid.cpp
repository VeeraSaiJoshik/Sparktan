#include "main.h"
#include "iostream"
#include "fstream"
#include "chrono"
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
    if(distanceClockWise < distanceCounterClockWise * -1){
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
    /*float Kp = 0.73;
    float Ki = 0.0254;
    float Kd = 2.5;*/
    float error= getAngularError(imuController.get_heading(), targetAngle);
    /*
    float Kp = 0.775;
    float Ki = 0.034;
    if(error <= 30){
        Ki = 0.0135;
    }
    else if(error <= 90){
        Ki = 0.027;
    }*/
    float Kp = 1.15;
    float Ki = 0.0265;
    float Kd = 4.2;
    float integral = 0;
    double derivative;
    double throttleSpeed;
    bool calculateIntegral = true;
    float curPosition = imuController.get_heading();
    float prevError = getAngularError(curPosition, targetAngle);
    auto start = std::chrono::high_resolution_clock::now();
    double time = 0;
    FILE* dataFile = fopen("/usd/rotationLogo.txt", "w");
    while(true){
        if(time > 2000)break;
        error = getAngularError(imuController.get_heading(), targetAngle);
        pros::lcd::set_text(0, "Error : " + std::to_string(error) + "," + std::to_string(getDriveTrainVelocity()));
        if(fabs(getAngularError(imuController.get_heading(), targetAngle)) < 0.4 && fabs(throttleSpeed) < 25){
            brakeDriveTrain();
            break;
        }
        derivative = error - prevError;
        if(fabs(error) <= 20)integral += error;
        else integral = 0;
        throttleSpeed = Kp * error + Kd * derivative + Ki * integral;
        moveDriveTrain(clampMotorVoltage(throttleSpeed));
        //Time, Current Position, Target Throttle, Actual Throttle Left Motor, Actual Throttle Right Motor, Actual Throttle Left Back Motor, Actual Thorttle Right Back Motor, Error
        double rearLeftMotorVelocity = rearLeftMotor.get_voltage();
        double rearRightMotorVelocity = rearRightMotor.get_voltage();
        double frontLeftMotorVelocity = frontLeftMotor.get_voltage();
        double frontRightMotorVelocity = frontRightMotor.get_voltage();
        fprintf(dataFile, "%f,%f,%f,%f,%f,%f,%f,%f\n", time, throttleSpeed, frontLeftMotorVelocity, frontRightMotorVelocity, rearLeftMotorVelocity, rearRightMotorVelocity, error);
        prevError = error;
        pros::delay(2);
        time += 10;
    }
    fclose(dataFile);
    pros::delay(100);
}

void rotateRobotBy(double targetDegrees){
    rotateRobotTo(normalizeAngle(imuController.get_heading() + targetDegrees));
}
//! Movment
void moveRobotBy(double inches){
    int wheelRadius = 2;
    int moveTicks = (inches * 450)/(wheelRadius * 3.141592653) * 5.0/7 * (0.955);
    int targetTicks = rearLeftMotor.get_position() + moveTicks;
    pros::lcd::set_text(1, std::to_string(targetTicks));
    int maxVolts = 90;
    
    if(inches <= 10) maxVolts = 40;
    if(inches < 0) maxVolts = -1 * maxVolts;
    // use inbuilt PID to complete the distance
    rearLeftMotor.move_relative(moveTicks, maxVolts);
    frontLeftMotor.move_relative(moveTicks, maxVolts);
    rearRightMotor.move_relative(moveTicks, maxVolts);
    frontRightMotor.move_relative(moveTicks, maxVolts);
    while (!((rearLeftMotor.get_position() < targetTicks + 5) && (rearLeftMotor.get_position() > targetTicks - 5))){
        pros::lcd::set_text(2, std::to_string(rearLeftMotor.get_position()));
        pros::delay(2);
    }
    brakeDriveTrain();
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
    pros::lcd::set_text(2, "started");
    int time = 0;
    bool startTime = -1;
    pros::lcd::set_text(2, "started1");
    pros::lcd::set_text(2, "started2");
    rotateDriveTrainWithVelocity(targetRPM);
    FILE* usd_file_write = fopen("/usd/RPMThrustTest2.txt", "w");
    
    
    while(true){
        double averageVelocity = getDriveTrainVelocity();
        if(time >= 2000) break;
        double rearLeftMotorVelocity = rearLeftMotor.get_actual_velocity();
        double rearRightMotorVelocity = rearRightMotor.get_actual_velocity();
        double frontLeftMotorVelocity = frontLeftMotor.get_actual_velocity();
        double frontRightMotorVelocity = frontRightMotor.get_actual_velocity();
        fprintf(usd_file_write, "%d,%f,%f,%f,%f\n", time, rearLeftMotorVelocity, rearRightMotorVelocity, frontLeftMotorVelocity, frontRightMotorVelocity);
        pros::lcd::set_text(3, std::to_string(rearLeftMotor.get_actual_velocity()));
        time = time + 2;
        pros::delay(2);
    }
    fclose(usd_file_write);
    dataLog.close();
    brakeDriveTrain();
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
