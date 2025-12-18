#ifndef CONFIG_H
#define CONFIG_H

// motor configuration
#define STEPS_PER_REV 200
#define MICROSTEPS 16
#define STEPS_PER_90_DEG (STEPS_PER_REV * MICROSTEPS / 4)

#define MAX_SPEED 1000.0
#define ACCELERATION 500.0

// timing
#define GRIPPER_MOVE_DELAY 10
#define STATE_TRANSITION_DELAY 500
#define MOTOR_TIMEOUT_MS 5000

// serial
#define SERIAL_BAUD 115200

#endif

