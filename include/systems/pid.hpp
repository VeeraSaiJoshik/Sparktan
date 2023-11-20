#pragma once
//^ General Functions
double clampMotorVoltage(double motorVoltage);
//^ Error Functions
double getAngularError(double startingAngle, double endingAngle);
double getErrorCounterclockwise(double staringAngle, double targetAngle);
double getErrorClockwise(double staringAngle, double targetAngle);
//^ PID Functions
void rotateRobotTo(double targetAngle);
void rotateRobotBy(double targetDegrees);
//^ Autotune Functions
void autoTunePID();
void robotRotationModel();
void gatherRotationalModelDataPoints();