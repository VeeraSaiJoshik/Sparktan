#pragma once
//^ General Functions
double clampMotorVoltage(double motorVoltage);
//^ Error Functions
double getAngularError(double startingAngle, double endingAngle);
double getCounterClockwiseError(double staringAngle, double targetAngle);
double getClockwiseError(double staringAngle, double targetAngle);
//^ PID Functions
//! Rotational
void rotateRobotTo(double targetAngle);
void rotateRobotBy(double targetDegrees);
void moveRobotByPID(double distance);
void moveRobotByPIDLambda(int distance, int trigger1, int trigger2);
//! Movement
void moveRobotBy(double inches);
void testerFunction();
//^ Autotune Functions
void autoTunePID();
void robotRotationModel();
void gatherRotationalModelDataPoints();
//^ Measurement Functions
void measureMotorRPMChange(int rpm);
void measureDeltaChangeBasedonRPM();