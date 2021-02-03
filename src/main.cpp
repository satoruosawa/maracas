#include <M5StickCPlus.h>

void setup() {
  M5.begin();
  M5.IMU.Init();
  M5.Beep.begin();
}

void loop() {
  M5.update();
  M5.Beep.update();
  static bool beepState = true;
  if (M5.BtnA.wasPressed()) {
    Serial.println("wasPressed");
    beepState = !beepState;
  }
  if (beepState) {
    float accX = 0.0;
    float accY = 0.0;
    float accZ = 0.0;
    M5.IMU.getAccelData(&accX, &accY, &accZ);
    float absAcc = abs(accX) + abs(accY) + abs(accZ);
    float calcCoef = 1000.0;
    float fromMin = 0.0;
    float fromMax = 5.0;
    float toMin = 0.0;
    float toMax = 1.0;
    float norm = map(absAcc * calcCoef, fromMin * calcCoef, fromMax * calcCoef,
                     toMin * calcCoef, toMax * calcCoef) /
                 calcCoef;
    norm = constrain(norm, toMin, toMax);
    // Serial.println(norm);
    uint16_t freq = pow(1000, norm);
    Serial.println(freq);

    M5.Beep.tone(freq, 100);
    delay(100);
  }
}