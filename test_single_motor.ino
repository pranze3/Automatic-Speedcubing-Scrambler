// simple test sketch for a single stepper motor
// use this to verify wiring and calibration before running full system

#include <AccelStepper.h>

#define STEP_PIN 2
#define DIR_PIN 3

AccelStepper motor(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {
  Serial.begin(115200);
  
  motor.setMaxSpeed(1000);
  motor.setAcceleration(500);
  
  Serial.println("single motor test");
  Serial.println("motor will rotate 90 degrees, then reverse");
}

void loop() {
  Serial.println("moving forward 90 degrees...");
  motor.move(800);
  
  while (motor.distanceToGo() != 0) {
    motor.run();
  }
  
  delay(1000);
  
  Serial.println("moving backward 90 degrees...");
  motor.move(-800);
  
  while (motor.distanceToGo() != 0) {
    motor.run();
  }
  
  delay(2000);
}

