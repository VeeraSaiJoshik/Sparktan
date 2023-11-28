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
//! Movement
void moveRobotBy(double inches);
void shove();
//^ Autotune Functions
void autoTunePID();
void robotRotationModel();
void gatherRotationalModelDataPoints();
//^ Measurement Functions
void measureMotorRPMChange();
void measureDeltaChangeBasedonRPM();