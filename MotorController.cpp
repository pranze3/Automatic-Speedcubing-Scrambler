#include "MotorController.h"

void MotorController::init() {
  for (int i = 0; i < MAX_MOTORS; i++) {
    motors[i] = nullptr;
  }
  
  motors[0] = new AccelStepper(AccelStepper::DRIVER, MOTOR_R_STEP, MOTOR_R_DIR);
  motors[1] = new AccelStepper(AccelStepper::DRIVER, MOTOR_L_STEP, MOTOR_L_DIR);
  motors[2] = new AccelStepper(AccelStepper::DRIVER, MOTOR_U_STEP, MOTOR_U_DIR);
  motors[3] = new AccelStepper(AccelStepper::DRIVER, MOTOR_D_STEP, MOTOR_D_DIR);
  motors[4] = new AccelStepper(AccelStepper::DRIVER, MOTOR_F_STEP, MOTOR_F_DIR);
  motors[5] = new AccelStepper(AccelStepper::DRIVER, MOTOR_B_STEP, MOTOR_B_DIR);
  
  for (int i = 0; i < MAX_MOTORS; i++) {
    if (motors[i]) {
      motors[i]->setMaxSpeed(MAX_SPEED);
      motors[i]->setAcceleration(ACCELERATION);
      motors[i]->setEnablePin(-1);
    }
  }
}

void MotorController::update() {
  for (int i = 0; i < MAX_MOTORS; i++) {
    if (motors[i]) {
      motors[i]->run();
    }
  }
}

void MotorController::executeMove(MoveCommand cmd) {
  if (!cmd.valid) {
    return;
  }
  
  int motorIdx = faceToMotorIndex(cmd.face);
  if (motorIdx < 0 || motorIdx >= MAX_MOTORS || !motors[motorIdx]) {
    return;
  }
  
  long steps = moveTypeToSteps(cmd.type);
  motors[motorIdx]->move(steps);
  
  waitForMotors();
}

bool MotorController::isBusy() {
  for (int i = 0; i < MAX_MOTORS; i++) {
    if (motors[i] && motors[i]->distanceToGo() != 0) {
      return true;
    }
  }
  return false;
}

int MotorController::faceToMotorIndex(Face face) {
  switch (face) {
    case FACE_R: return 0;
    case FACE_L: return 1;
    case FACE_U: return 2;
    case FACE_D: return 3;
    case FACE_F: return 4;
    case FACE_B: return 5;
    default: return -1;
  }
}

long MotorController::moveTypeToSteps(MoveType type) {
  switch (type) {
    case MOVE_CW:
      return STEPS_PER_90_DEG;
    case MOVE_CCW:
      return -STEPS_PER_90_DEG;
    case MOVE_DOUBLE:
      return STEPS_PER_90_DEG * 2;
    default:
      return STEPS_PER_90_DEG;
  }
}

void MotorController::waitForMotors() {
  unsigned long startTime = millis();
  while (isBusy() && (millis() - startTime < 5000)) {
    update();
    delay(1);
  }
}

