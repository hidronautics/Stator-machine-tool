#ifndef MOTOR_H
#define MOTOR_H

#define MOTOR_INTERFACE_TYPE 1 //1 означает внешний шаговый драйвер с выводами Step и Direction

#define ACCELERATION 3000
#define MAX_SPEED 60000


#include <AccelStepper.h>

class Motor {
public:
    int stepPin;
    int dirPin;
    int limitPin;
    int stepsPerUnit;

    AccelStepper accelStepper;

    Motor(int stepPin, int dirPin, int limitPin, int stepsPerUnit) : accelStepper(MOTOR_INTERFACE_TYPE, stepPin, dirPin) {
    };

    Motor(int stepPin, int dirPin, int stepsPerUnit) : accelStepper(MOTOR_INTERFACE_TYPE, stepPin, dirPin) {
    };

    void setup() {
        accelStepper.setMaxSpeed(MAX_SPEED);
        pinMode(limitPin, INPUT);

        accelStepper.setAcceleration(ACCELERATION);
    };

    void setHome() {
        accelStepper.setAcceleration(300000000);

        while(digitalRead(limitPin) == 1) {
            accelStepper.moveTo(accelStepper.currentPosition() + (stepsPerUnit * -0.3));
            accelStepper.runSpeedToPosition();
        };
        accelStepper.setCurrentPosition(0);

        accelStepper.setMaxSpeed(MAX_SPEED);
    }

    void moveTo(double distance) {
        accelStepper.moveTo(stepsPerUnit * distance);
        accelStepper.runSpeedToPosition();
    };

};

#endif // MOTOR_H
