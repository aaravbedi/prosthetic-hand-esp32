#pragma once

#define NUM_FINGERS 5

static const int SERVO_PINS[NUM_FINGERS] = {
  13, // Thumb
  12, // Index
  14, // Middle
  27, // Ring
  26  // Little
};

static const int SENSOR_PINS[NUM_FINGERS] = {
  34, // Thumb sensor
  35, // Index sensor
  32, // Middle sensor
  33, // Ring sensor
  39  // Little sensor
};

static const int HAPTIC_PINS[NUM_FINGERS] = {
  25, // Thumb motor
  23, // Index motor
  22, // Middle motor
  21, // Ring motor
  19  // Little motor
};

#define LOOP_INTERVAL_MS   20      // ~50 Hz update
#define FILTER_ALPHA       0.3f    // 0–1, higher = more responsive
#define FINGER_OPEN_ANGLE  10      // degrees
#define FINGER_CLOSED_ANGLE 140    // degrees
#define MAX_DEG_PER_STEP   4       // max angle change per loop
#define DEADZONE           0.05f
#define PRESSURE_EXPONENT  1.6f
#define HAPTIC_CONTACT_THRESHOLD   0.25f  // "object contact"
#define HAPTIC_TOO_HARD_THRESHOLD  0.65f  // "squeezing too hard"
#define HAPTIC_MEDIUM_PWM  110
#define HAPTIC_MAX_PWM     220
