#include "GripperController.h"

void GripperController::init() {
  gripperServo.attach(GRIPPER_SERVO_PIN);
  clamped = false;
  targetPosition = GRIPPER_RELEASED_POS;
  currentPosition = GRIPPER_RELEASED_POS;
  gripperServo.write(currentPosition);
  delay(500);
}

void GripperController::update() {
  if (currentPosition != targetPosition) {
    if (currentPosition < targetPosition) {
      currentPosition++;
    } else {
      currentPosition--;
    }
    gripperServo.write(currentPosition);
    delay(10);
  }
}

void GripperController::setClamped(bool shouldClamp) {
  //checking whether it has actually clamped
  clamped = shouldClamp;
  targetPosition = shouldClamp ? GRIPPER_CLAMPED_POS : GRIPPER_RELEASED_POS;
}

bool GripperController::isClamped() {
  return clamped && (currentPosition == targetPosition);
}


