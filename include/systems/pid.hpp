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
//! Movement
void moveRobotBy(double inches);
//^ Autotune Functions
void autoTunePID();
void robotRotationModel();
void gatherRotationalModelDataPoints();
//^ Measurement Functions
void measureMotorRPMChange(int rpm);
void measureDeltaChangeBasedonRPM();