/*
 * DingDinDing bell sound example for the toneAC library,
 * https://github.com/teckel12/arduino-toneac
 *
 * this example demonstrates usefulness of volume control
 * and how to make control sound without blocking the loop.
 *
 * created 20 Jun 2020
 * by Juraj Andrassy
 */
#include <toneAC.h>

const unsigned BELL_REPEAT_INTERVAL = 10000; // miliseconds

void setup() {
}

void loop() {

  unsigned long currentMillis = millis();
  bool ringTheBell = true;

  // put your kitchen timer or oven control code here
  // and set ringTheBell variable accordingly to code logic

  if (ringTheBell) {
    static unsigned long bellStartMillis;
    bool restartBell = false;
    if (currentMillis - bellStartMillis > BELL_REPEAT_INTERVAL || !bellStartMillis) {
      bellStartMillis = currentMillis;
      restartBell = true;
    }
    bellSound(restartBell);
  }
}

void bellSound(bool restart) {
  const byte REPEAT_COUNT = 3;
  const int BELL_FREQUENCY = 4186;
  const unsigned short LENGTH = 1200;
  const byte VOLUME_STEPS = 9;
  const unsigned short STEP_LENGTH = LENGTH / VOLUME_STEPS;

  static byte volume = VOLUME_STEPS;
  static byte count = 0;
  static unsigned long previousMillis;

  unsigned long currentMillis = millis();

  if (restart) {
    count = 0;
    volume = VOLUME_STEPS;
  }
  if (count == REPEAT_COUNT)
    return;
  if (currentMillis - previousMillis > STEP_LENGTH) {
    previousMillis = currentMillis;
    toneAC(BELL_FREQUENCY, volume, STEP_LENGTH * 2, true);
    volume--;
    if (volume == 0) {
      volume = VOLUME_STEPS;
      count++;
    }
  }
}
