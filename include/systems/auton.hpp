#pragma once
#include "main.h"
//? Command Class
enum autonCommandType{
    move = 0,
    rotate = 1, 
    catapult = 2, 
    wingIn = 3, 
    wingOut = 4, 
    intake = 6, 
    outtake = 7, 
    stopIntake = 8, 
    shove = 9
};
class autonCommand{
    public : 
        autonCommandType type;
        double parameter = 0;
        autonCommand(autonCommandType typeTemp, double parameterTemp = 0){
            type = typeTemp;
            parameter = parameterTemp;            
        }
        void runCommand(){
            switch(type){
                case move:
                    moveForward(parameter);
                    break;
                case rotate:
                    rotateTo(parameter);
                    break;
                case catapult:
                    shootCatapult();
                    break;
                case wingIn:
                    pullWingsIn();
                    break;
                case wingOut:
                    pullWingsOut();
                    break;
                case intake:
                    runIntake(parameter);
                    break;
                case outtake:
                    runOuttake(parameter);
                    break;
                case stopIntake:
                    haltIntakeOutake();
                    break;
                case shove:
                    shoveIn();
                    break;
            }
        }
};
//? Command Decryption Commands
std::vector<std::string> split();
autonCommand decodeString();
std::vector<autonCommand> processEncodedString();
//? Robot Movement Functions
void moveForward(double inches);
void rotateTo(double degrees);
void shootCatapult();
void pullWingsIn();
void pullWingsOut();
void runIntake(int milliseconds);
void runOuttake(int milliseconds);
void haltIntakeOutake();
void shoveIn();