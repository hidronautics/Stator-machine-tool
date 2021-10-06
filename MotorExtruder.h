#ifndef MOTOREXTRUDOR_H
#define MOTOREXTRUDOR_H

#define MOTOR_INTERFACE_TYPE 1 //1 означает внешний шаговый драйвер с выводами Step и Direction
#define ACCELERATION 3000
#define MAX_SPEED 60000


#include <AccelStepper.h>

class MotorExtruder {
public:
    int stepPin;
    int dirPin;
    int stepsPerMm;

    AccelStepper accelStepper;

    MotorExtruder(int stepPin, int dirPin, int stepsPerMm) : accelStepper(MOTOR_INTERFACE_TYPE, stepPin, dirPin) {

    };

    void setup() {
        accelStepper.setMaxSpeed(MAX_SPEED);
        accelStepper.setAcceleration(ACCELERATION);
    };

    void moveTo(double distance) {
        accelStepper.moveTo(int(stepsPerMm * distance));
        accelStepper.runSpeedToPosition();
    };
};
#endif // MOTOREXTRUDOR_H
