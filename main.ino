#include "Mechanics.h"

Mechanics mechanics;

void setup() {
    mechanics.driverEnable();

    mechanics.table.setHome();
    mechanics.carriage.setHome();

    long positions[2];
    positions[0] = 30000;
    positions[1] = 10000;
    mechanics.steppers.moveTo(positions);
    mechanics.steppers.runSpeedToPosition();

}

void loop() {

}
