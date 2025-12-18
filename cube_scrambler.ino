#include "StateMachine.h"
#include "MotorController.h"
#include "CubeParser.h"
#include "GripperController.h"

StateMachine stateMachine;
MotorController motorController;
CubeParser parser;
GripperController gripper;

String inputBuffer = "";
bool newCommand = false;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
  
  motorController.init();
  gripper.init();
  stateMachine.init();
  
  Serial.println("cube scrambler ready");
  Serial.println("send scramble sequence (WCA notation)");
}

void loop() {
  stateMachine.update();
  
  if (stateMachine.getState() == STATE_IDLE) {
    handleSerialInput();
  }
  
  if (newCommand && stateMachine.getState() == STATE_IDLE) {
    processScrambleCommand();
    newCommand = false;
  }
  
  motorController.update();
  gripper.update();
}

void handleSerialInput() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    
    if (c == '\n' || c == '\r') {
      if (inputBuffer.length() > 0) {
        newCommand = true;
      }
    } else {
      inputBuffer += c;
    }
  }
}

void processScrambleCommand() {
  Serial.print("parsing: ");
  Serial.println(inputBuffer);
  
  if (parser.parse(inputBuffer)) {
    stateMachine.transitionTo(STATE_CLAMPING);
    Serial.println("command parsed, starting scramble sequence");
  } else {
    Serial.println("parse error - invalid notation");
  }
  
  inputBuffer = "";
}

