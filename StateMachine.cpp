#include "StateMachine.h"
#include "MotorController.h"
#include "CubeParser.h"
#include "GripperController.h"

extern MotorController motorController;
extern CubeParser parser;
extern GripperController gripper;

void StateMachine::init() {
  currentState = STATE_IDLE;
  stateStartTime = millis();
  stateTimeout = 0;
}

void StateMachine::update() {
  switch (currentState) {
    case STATE_IDLE:
      handleIdle();
      break;
    case STATE_CLAMPING:
      handleClamping();
      break;
    case STATE_SCRAMBLING:
      handleScrambling();
      break;
    case STATE_RELEASING:
      handleReleasing();
      break;
  }
}

void StateMachine::transitionTo(SystemState newState) {
  currentState = newState;
  stateStartTime = millis();
  stateTimeout = 0;
}

void StateMachine::handleIdle() {
  // just waiting for commands
}

void StateMachine::handleClamping() {
  if (millis() - stateStartTime < 100) {
    return;
  }
  
  gripper.setClamped(true);
  
  if (gripper.isClamped()) {
    delay(500);
    transitionTo(STATE_SCRAMBLING);
  }
}

void StateMachine::handleScrambling() {
  if (!parser.hasMoreMoves()) {
    transitionTo(STATE_RELEASING);
    return;
  }
  
  if (motorController.isBusy()) {
    return;
  }
  
  MoveCommand cmd = parser.getNextMove();
  motorController.executeMove(cmd);
}

void StateMachine::handleReleasing() {
  if (millis() - stateStartTime < 100) {
    return;
  }
  
  gripper.setClamped(false);
  
  if (!gripper.isClamped()) {
    delay(500);
    parser.reset();
    transitionTo(STATE_IDLE);
    Serial.println("scramble complete");
  }
}

