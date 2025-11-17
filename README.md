# prosthetic-hand-esp32
ESP32-based glove-controlled prosthetic hand with MG90S servos, pressure sensors, and vibration feedback.

The firmware does three main things:
- Reads analog values from pressure sensors on the glove.
- Converts those readings into target angles for each servo on the prosthetic hand.
- Activates vibration motors when grip force crosses certain thresholds.

Each finger has:
- one pressure sensor input,
- one servo output on the prosthetic hand,
- one vibration motor in the glove.
