#include "main.h"

void driveTrainFunction(){
    JoystickValues leftJoyStick = JoystickValues(leftSideJoyStick);
    JoystickValues rightJoyStick = JoystickValues(rightSideJoyStick);
    if(driveTrainMode == Arcade){
        if(leftJoyStick.joyStickUsed()){
            arcadeDrive(leftJoyStick);
        }else if(rightJoyStick.joyStickUsed()){
            arcadeDrive(rightJoyStick);
        }else{
            brakeDriveTrain();
        }
    }else{
    }
}
void brakeDriveTrain(){
    frontLeftMotor.brake();
    frontRightMotor.brake();
    rearLeftMotor.brake();
    rearRightMotor.brake();
}
void moveDriveTrain(double voltage){
    frontLeftMotor = voltage;
    frontRightMotor = voltage;
    rearLeftMotor = voltage;
    rearRightMotor = voltage;
}
void moveRightDrive(double voltage){
    frontRightMotor = voltage;
    rearLeftMotor = voltage;
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
    moveLeftDrive(leftJoyStick.xValue);
    moveRightDrive(rightJoyStick.xValue);
}
void arcadeDrive(JoystickValues joyStick){
    moveLeftDrive((joyStick.yValue - joyStick.xValue)/(127.0 * 127.0));
    moveRightDrive((joyStick.yValue + joyStick.xValue)/(127.0 * 127.0));
}
