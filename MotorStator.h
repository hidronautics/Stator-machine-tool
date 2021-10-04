#ifndef MOTORSTATOR_H
#define MOTORSTATOR_H

#define MOTOR_INTERFACE_TYPE 1

#include <AccelStepper.h>
#include "Motor.h"

class MotorStator {
public:
    int stepPin;
    int dirPin;
    int limitPin;

    AccelStepper accelStepper;
    int stepPer360;

    MotorStator(int stepPin, int dirPin, int stepPer360) : accelStepper(MOTOR_INTERFACE_TYPE, stepPin, dirPin) {

    };

    void moveTo(double grad) {
        accelStepper.moveTo(int(stepPer360 / 360 * grad));
        accelStepper.runSpeedToPosition();
    };

};
#endif // MOTORSTATOR_H
