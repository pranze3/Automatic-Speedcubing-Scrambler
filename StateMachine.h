#ifndef STATEMACHINE_H
#define STATEMACHINE_H

enum SystemState {
  STATE_IDLE,
  STATE_CLAMPING,
  STATE_SCRAMBLING,
  STATE_RELEASING
};

class StateMachine {
public:
  void init();
  void update();
  SystemState getState() { return currentState; }
  void transitionTo(SystemState newState);
  
private:
  SystemState currentState;
  unsigned long stateStartTime;
  unsigned long stateTimeout;
  
  void handleIdle();
  void handleClamping();
  void handleScrambling();
  void handleReleasing();
};

#endif

