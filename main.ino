#define MOTOR_INTERFACE_TYPE 1 //1 означает внешний шаговый драйвер с выводами Step и Direction

#define ACCELERATION 3000
#define MAX_SPEED 60000

#define CARRIAGE_STEP_PIN 2
#define CARRIAGE_DIR_PIN 5
#define CARRIAGE_LIMIT_PIN 9
#define CARRIAGE_STEPS_PER_MM 3200

#define TABLE_STEP_PIN 4
#define TABLE_DIR_PIN 7
#define TABLE_LIMIT_PIN 11
#define TABLE_STEPS_PER_MM 800


#include <AccelStepper.h>

class Motor {
public:
    int stepPin;
    int dirPin;
    int limitPin;
    int stepsPerMm;

    AccelStepper accelStepper;

    Motor(int stepPin, int dirPin, int limitPin, int stepsPerMm) :
            accelStepper(MOTOR_INTERFACE_TYPE, stepPin, dirPin) {
    };

    void setup() {
        accelStepper.setMaxSpeed(MAX_SPEED);
        pinMode(limitPin, INPUT);

        accelStepper.setAcceleration(ACCELERATION);
    };

    void setHome() {
        accelStepper.setAcceleration(300000000);

        while (digitalRead(limitPin) == 1) {
            accelStepper.moveTo(accelStepper.currentPosition() + (stepsPerMm * -0.3));
            accelStepper.runSpeedToPosition();
        };
        accelStepper.setCurrentPosition(0);

        accelStepper.setMaxSpeed(MAX_SPEED);
    }

    void moveTo(double distance) {
        accelStepper.moveTo(int(stepsPerMm * distance));
        accelStepper.runSpeedToPosition();
    };

};

Motor carriage(CARRIAGE_STEP_PIN,
               CARRIAGE_DIR_PIN,
               CARRIAGE_LIMIT_PIN,
               CARRIAGE_STEPS_PER_MM);

Motor table(TABLE_STEP_PIN,
            TABLE_DIR_PIN,
            TABLE_LIMIT_PIN,
            TABLE_STEPS_PER_MM);

void driveEnable() {
    pinMode(8, OUTPUT);
    digitalWrite(8, 0);
}

void setup() {
    driveEnable();
    table.setup();
    carriage.setup();

    table.setHome();
    carriage.setHome();

}

void loop() {
    carriage.moveTo(70);
    table.moveTo(60);
}
