#include "Motor.h"
#include "MotorStator.h"

#include <AccelStepper.h>
#include <MultiStepper.h>

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

Motor carriage(CARRIAGE_STEP_PIN,
               CARRIAGE_DIR_PIN,
               CARRIAGE_LIMIT_PIN,
               CARRIAGE_STEPS_PER_MM);

Motor table(TABLE_STEP_PIN,
            TABLE_DIR_PIN,
            TABLE_LIMIT_PIN,
            TABLE_STEPS_PER_MM);

Motor extruder(EXTRUDER_STEP_PIN,
               EXTRUDER_DIR_PIN,
               0,
               EXTRUDER_STEPS_PER_MM);

MotorStator stator(STATOR_STEP_PIN,
                   STATOR_DIR_PIN,
                   STATOR_STEPS_PER_360);

MultiStepper steppers;

void driveEnable() {
    pinMode(8, OUTPUT);
    digitalWrite(8, 0);
}

void setup() {
    steppers.addStepper(carriage.accelStepper);
    steppers.addStepper(table.accelStepper);
    steppers.addStepper(extruder.accelStepper);
    steppers.addStepper(stator.accelStepper);

//    carriage(CARRIAGE_STEP_PIN,
//                         CARRIAGE_DIR_PIN,
//                         CARRIAGE_LIMIT_PIN,
//                         CARRIAGE_STEPS_PER_MM);
//
//    table(TABLE_STEP_PIN,
//                      TABLE_DIR_PIN,
//                      TABLE_LIMIT_PIN,
//                      TABLE_STEPS_PER_MM);
//
//    stator = new MotorStator(EXTRUDER_STEP_PIN,
//                             EXTRUDER_DIR_PIN,
//                             EXTRUDER_STEPS_PER_MM);
//
//    extruder = new Motor(STATOR_STEP_PIN,
//                         STATOR_DIR_PIN,
//                         STATOR_STEPS_PER_360);

    driveEnable();
    table.setup();
    carriage.setup();

    table.setHome();
    carriage.setHome();


    long positions[2];
    positions[0] = 30000;
    positions[1] = 10000;
    steppers.moveTo(positions);
    steppers.runSpeedToPosition();

}

void loop() {
    carriage.moveTo(70);
    table.moveTo(60);
}
