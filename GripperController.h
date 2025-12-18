#ifndef GRIPPERCONTROLLER_H
#define GRIPPERCONTROLLER_H

#define GRIPPER_SERVO_PIN A0
#define GRIPPER_CLAMPED_POS 90
#define GRIPPER_RELEASED_POS 0

#include <Servo.h>

class GripperController {
public:
  void init();
  void update();
  void setClamped(bool clamped);
  bool isClamped();
  
private:
  Servo gripperServo;
  bool clamped;
  int targetPosition;
  int currentPosition;
};

#endif

