#ifndef TABLE_H
#define TABLE_H

#define MOTOR_INTERFACE_TYPE 1 //1 означает внешний шаговый драйвер с выводами Step и Direction
#define TABLE_STEP_PIN 4
#define TABLE_DIR_PIN 7
#define TABLE_LIMIT_PIN 11

#define TABLE_STEPS_PER_MM 800
#define TABLE_ACCELERATION 3000
#define TABLE_MAX_SPEED 160000


#include <AccelStepper.h>

class Table {
public:
    Table() : accelStepper(MOTOR_INTERFACE_TYPE, TABLE_STEP_PIN, TABLE_DIR_PIN) {
    };

    void setup() {
        accelStepper.setMaxSpeed(TABLE_MAX_SPEED);
        pinMode(TABLE_LIMIT_PIN, INPUT);

        accelStepper.setAcceleration(TABLE_ACCELERATION);
    };

    void setHome() {
        accelStepper.setAcceleration(30000000);

        while(digitalRead(TABLE_LIMIT_PIN) == 1) {
            accelStepper.moveTo(accelStepper.currentPosition() + (TABLE_STEPS_PER_MM * -0.3));
            accelStepper.runSpeedToPosition();
        };
        accelStepper.setCurrentPosition(0);

        accelStepper.setMaxSpeed(TABLE_MAX_SPEED);
    };

    void moveTo(double distance) {
        accelStepper.moveTo(TABLE_STEPS_PER_MM * distance);
        accelStepper.runSpeedToPosition();
    };



    AccelStepper accelStepper;
};


#endif //TABLE_H
