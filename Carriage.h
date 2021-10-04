#ifndef CARRIAGE_H
#define CARRIAGE_H

#define MOTOR_INTERFACE_TYPE 1 //1 означает внешний шаговый драйвер с выводами Step и Direction
#define CARRIAGE_STEP_PIN 2
#define CARRIAGE_DIR_PIN 5
#define CARRIAGE_LIMIT_PIN 9

#define CARRIAGE_STEPS_PER_MM 3200
#define CARRIAGE_ACCELERATION 3000
#define CARRIAGE_MAX_SPEED 60000


#include <AccelStepper.h>

class Carriage {
public:
    Carriage() : accelStepper(MOTOR_INTERFACE_TYPE, CARRIAGE_STEP_PIN, CARRIAGE_DIR_PIN) {
    };

    void setup() {
        accelStepper.setMaxSpeed(CARRIAGE_MAX_SPEED);
        pinMode(CARRIAGE_LIMIT_PIN, INPUT);

        accelStepper.setAcceleration(CARRIAGE_ACCELERATION);
    };

    void setHome() {
        accelStepper.setAcceleration(300000000);

        while(digitalRead(CARRIAGE_LIMIT_PIN) == 1) {
            accelStepper.moveTo(accelStepper.currentPosition() + (CARRIAGE_STEPS_PER_MM * -0.3));
            accelStepper.runSpeedToPosition();
        };
        accelStepper.setCurrentPosition(0);

        accelStepper.setMaxSpeed(CARRIAGE_MAX_SPEED);
    }

    void moveTo(double distance) {
        accelStepper.moveTo(CARRIAGE_STEPS_PER_MM * distance);
        accelStepper.runSpeedToPosition();
    };



    AccelStepper accelStepper;
};

#endif // CARRIAGE_H
