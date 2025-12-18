#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "CubeParser.h"
#include <AccelStepper.h>

#define MAX_MOTORS 6

#define MOTOR_R_STEP 2
#define MOTOR_R_DIR 3
#define MOTOR_L_STEP 4
#define MOTOR_L_DIR 5
#define MOTOR_U_STEP 6
#define MOTOR_U_DIR 7
#define MOTOR_D_STEP 8
#define MOTOR_D_DIR 9
#define MOTOR_F_STEP 10
#define MOTOR_F_DIR 11
#define MOTOR_B_STEP 12
#define MOTOR_B_DIR 13

#define STEPS_PER_REV 200
#define MICROSTEPS 16
#define STEPS_PER_90_DEG (STEPS_PER_REV * MICROSTEPS / 4)

#define MAX_SPEED 1000.0
#define ACCELERATION 500.0

class MotorController {
public:
  void init();
  void update();
  void executeMove(MoveCommand cmd);
  bool isBusy();
  
private:
  AccelStepper* motors[MAX_MOTORS];
  int faceToMotorIndex(Face face);
  long moveTypeToSteps(MoveType type);
  void waitForMotors();
};

#endif

