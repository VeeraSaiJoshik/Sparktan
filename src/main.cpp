#include "main.h"

using namespace pros;

void initialize() {}
void disabled() {}
void competition_initialize() {}
void autonomous() {}
void opcontrol() {
    Task primary(primaryOperatorControl);
    Task secondary(secondaryOperatorControl);
    Task tertiary(tertiaryOperatorControl);
}