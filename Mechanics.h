#ifndef MECHANICS_H
#define MECHANICS_H

#include "Motor.h"
#include "MotorStator.h"
#include "MotorExtruder.h"

#include <MultiStepper.h>

#define DRIVER_ENABLE_PIN 8

#define CARRIAGE_STEP_PIN 2
#define CARRIAGE_DIR_PIN 5
#define CARRIAGE_LIMIT_PIN 9
#define CARRIAGE_STEPS_PER_MM 3200

#define TABLE_STEP_PIN 4
#define TABLE_DIR_PIN 7
#define TABLE_LIMIT_PIN 11
#define TABLE_STEPS_PER_MM 800

#define EXTRUDER_STEP_PIN 3
#define EXTRUDER_DIR_PIN 6
#define EXTRUDER_STEPS_PER_MM 160

#define STATOR_STEP_PIN 4
#define STATOR_DIR_PIN 7
#define STATOR_STEPS_PER_360 12800

class Mechanics {
public:
    Motor carriage;
    Motor table;
    MotorExtruder extruder;
    MotorStator stator;

    MultiStepper steppers;

    Mechanics() :
            carriage(CARRIAGE_STEP_PIN, CARRIAGE_DIR_PIN, CARRIAGE_LIMIT_PIN, CARRIAGE_STEPS_PER_MM),
            table(TABLE_STEP_PIN, TABLE_DIR_PIN, TABLE_LIMIT_PIN, TABLE_STEPS_PER_MM),
            extruder(EXTRUDER_STEP_PIN, EXTRUDER_DIR_PIN, EXTRUDER_STEPS_PER_MM),
            stator(STATOR_STEP_PIN, STATOR_DIR_PIN, STATOR_STEPS_PER_360) {

        steppers.addStepper(carriage.accelStepper);
        steppers.addStepper(table.accelStepper);
        steppers.addStepper(extruder.accelStepper);
        steppers.addStepper(stator.accelStepper);
        driverEnable();
    };

    void setup() {
        carriage.setup();
        table.setup();
        extruder.setup();
        stator.setup();
    };

    void setHome() {
        table.setHome();
        carriage.setHome();
    };

    void driverEnable() {
        pinMode(DRIVER_ENABLE_PIN, OUTPUT);
        digitalWrite(DRIVER_ENABLE_PIN, 0);
    }

//    void move(long deltaPos*){             // TODO:реализовать функцию по перемещению
//        steppers.moveTo(deltaPos);
//
//
//    }
};

#endif // MECHANICS_H
