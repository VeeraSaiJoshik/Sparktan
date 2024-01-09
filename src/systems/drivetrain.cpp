#include "main.h"
#include "cmath"

void driveTrainFunction(){
    JoystickValues leftJoyStick = JoystickValues(leftSideJoyStick);
    JoystickValues rightJoyStick = JoystickValues(rightSideJoyStick);
    if(driveTrainMode == Arcade){
        if(leftJoyStick.joyStickUsed()){
            arcadeDrive(leftJoyStick);
        }else{
            arcadeDrive(rightJoyStick);
        }
    }else{
        tankDrive(leftJoyStick, rightJoyStick);
    }
}
void brakeDriveTrain(){
    frontLeftMotor = 0;
    frontLeftMotor.brake();
    frontRightMotor = 0;
    frontRightMotor.brake();
    rearLeftMotor = 0;
    rearLeftMotor.brake();
    rearRightMotor = 0;
    rearRightMotor.brake();
}
void moveDriveTrain(double voltage){
    moveRightDrive(voltage);
    moveLeftDrive(voltage);
}
void moveRightDrive(int voltage){
    frontRightMotor = voltage;
    rearRightMotor = voltage;
}
void moveLeftDrive(double voltage){
    frontLeftMotor = voltage;
    rearLeftMotor = voltage;
}
void rotateDriveTrain(double voltage){
    moveRightDrive(-1 * voltage);
    moveLeftDrive(voltage);
}
void tankDrive(JoystickValues leftJoyStick, JoystickValues rightJoyStick){
    moveLeftDrive(leftJoyStick.yValue);
    moveRightDrive(rightJoyStick.yValue);
}
void arcadeDrive(JoystickValues joyStick){
    moveLeftDrive(pow((joyStick.yValue + joyStick.xValue),3)/(127.0 * 127.0));
    moveRightDrive(pow((joyStick.yValue - joyStick.xValue),3)/(127.0 * 127.0));
}
void moveDriveTrainAccurate(int millivolts){
    frontRightMotor.move_voltage(millivolts);
    frontLeftMotor.move_voltage(millivolts);
    rearRightMotor.move_voltage(millivolts);
    rearLeftMotor.move_voltage(millivolts);
}
void rotateDriveTrainAccurate(int millivots){
    frontRightMotor.move_voltage(millivots * -1);
    rearRightMotor.move_voltage(millivots * -1);
    frontLeftMotor.move_voltage(millivots);
    rearLeftMotor.move_voltage(millivots);
}
double getDriveTrainVoltage(){
    return (frontRightMotor.get_voltage() + frontLeftMotor.get_voltage() + rearLeftMotor.get_voltage() + rearRightMotor.get_voltage())/4.0;
}
double getDriveTrainVelocity(){
    return (frontRightMotor.get_actual_velocity() + frontLeftMotor.get_actual_velocity() + rearLeftMotor.get_actual_velocity() + rearRightMotor.get_actual_velocity())/4.0;
}
void moveDriveTrainWithVelocity(int velocity){
    frontRightMotor.move_velocity(velocity);
    frontLeftMotor.move_velocity(velocity);
    rearRightMotor.move_velocity(velocity);
    rearLeftMotor.move_velocity(velocity);
}
void rotateDriveTrainWithVelocity(int velocity){
    frontRightMotor.move_velocity(velocity * -1);
    rearRightMotor.move_velocity(velocity * -1);
    frontLeftMotor.move_velocity(velocity);
    rearLeftMotor.move_velocity(velocity);
}