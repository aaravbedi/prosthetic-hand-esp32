# Wiring Notes – Prosthetic Hand ESP32 Prototype
## Power

- Servos powered from a separate 5V supply.
- ESP32 powered over USB.
- All grounds tied together:
  - ESP32 GND
  - 5V servo GND
  - sensor ground
  - haptic motor ground

## Servos

- 5x MG90S micro servos (thumb + 4 fingers).
- Signal pins match `SERVO_PINS` in `firmware/config.h`.
- Tendons (fishing line / PTFE) tied to servo horns and routed through the printed fingers.

## Pressure Sensors

- One sensor per finger on the control glove.
- Each sensor in a simple voltage divider:
  - 5V → fixed resistor → sensor → GND
  - midpoint goes to an ESP32 ADC pin listed in `SENSOR_PINS`.

---

## Haptic Motors

- Small coin or cylindrical vibration motors in the glove.
- Driven from 5V through NPN transistors with flyback diodes.
- Gate/base controlled by pins in `HAPTIC_PINS`.

Reminder : These notes are mostly here so I can recreate the setup later without digging through old notebooks.
