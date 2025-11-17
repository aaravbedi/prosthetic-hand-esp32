Servo fingerServos[NUM_FINGERS];
int fingerAngles[NUM_FINGERS];
float filteredPressure[NUM_FINGERS];

void attachServos() {
  for (int i = 0; i < NUM_FINGERS; i++) {
    fingerServos[i].attach(SERVO_PINS[i]);
    fingerServos[i].write(FINGER_OPEN_ANGLE);
    fingerAngles[i] = FINGER_OPEN_ANGLE;
    filteredPressure[i] = 0.0f;
  }
}

void setupPins() {
  for (int i = 0; i < NUM_FINGERS; i++) {
    pinMode(SENSOR_PINS[i], INPUT);
  }
  for (int i = 0; i < NUM_FINGERS; i++) {
    pinMode(HAPTIC_PINS[i], OUTPUT);
    analogWrite(HAPTIC_PINS[i], 0);
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("Prosthetic Hand – ESP32");
  Serial.println("Initializing...");
  setupPins();
  attachServos();
  Serial.println("Ready.");
}

int mapPressureToAngle(float filteredValue) {
  float normalized = filteredValue / 4095.0f; 

  if (normalized < DEADZONE) {
    normalized = 0.0f;
  }

  normalized = pow(normalized, PRESSURE_EXPONENT);

  int angleRange = FINGER_CLOSED_ANGLE - FINGER_OPEN_ANGLE;
  int target = FINGER_OPEN_ANGLE + (int)(normalized * angleRange);

  if (target < FINGER_OPEN_ANGLE) target = FINGER_OPEN_ANGLE;
  if (target > FINGER_CLOSED_ANGLE) target = FINGER_CLOSED_ANGLE;

  return target;
}

int pressureToHapticPWM(float normalized) {
  if (normalized > HAPTIC_TOO_HARD_THRESHOLD) {
    return HAPTIC_MAX_PWM;
  }
  if (normalized > HAPTIC_CONTACT_THRESHOLD) {
    return HAPTIC_MEDIUM_PWM;
  }
  return 0;
}

void loop() {
  static unsigned long lastUpdate = 0;
  unsigned long now = millis();

  if (now - lastUpdate < LOOP_INTERVAL_MS) {
    return;
  }
  lastUpdate = now;

  for (int i = 0; i < NUM_FINGERS; i++) {
    int raw = analogRead(SENSOR_PINS[i]);

    filteredPressure[i] =
      FILTER_ALPHA * raw + (1.0f - FILTER_ALPHA) * filteredPressure[i];

    float normalized = filteredPressure[i] / 4095.0f;
    if (normalized < DEADZONE) normalized = 0.0f;

    int targetAngle = mapPressureToAngle(filteredPressure[i]);

    int current = fingerAngles[i];
    int diff = targetAngle - current;

    if (abs(diff) > MAX_DEG_PER_STEP) {
      current += (diff > 0 ? MAX_DEG_PER_STEP : -MAX_DEG_PER_STEP);
    } else {
      current = targetAngle;
    }

    fingerAngles[i] = current;
    fingerServos[i].write(current);

    int pwm = pressureToHapticPWM(normalized);
    analogWrite(HAPTIC_PINS[i], pwm);

    Serial.print("F");
    Serial.print(i);
    Serial.print(" raw=");
    Serial.print(raw);
    Serial.print(" norm=");
    Serial.print(normalized, 2);
    Serial.print(" angle=");
    Serial.print(current);
    Serial.print(" pwm=");
    Serial.print(pwm);
    Serial.print("  |  ");
  }
  Serial.println();
}
