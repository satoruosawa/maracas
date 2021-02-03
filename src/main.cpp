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
    float absAcc = abs(accX);

    static float absAccAvg = absAcc;
    float avgCoef = 0.01;
    absAccAvg = absAccAvg * (1 - avgCoef) + absAcc * avgCoef;

    unsigned long interval = 100000;
    static unsigned long prevMicros = micros();
    if (micros() < prevMicros + interval) return;
    prevMicros = micros();
    float calcCoef = 1000.0;
    float fromMin = 0.0;
    float fromMax = 1.0;
    float toMin = 0.0;
    float toMax = 1.0;
    float norm = map(absAccAvg * calcCoef, fromMin * calcCoef,
                     fromMax * calcCoef, toMin * calcCoef, toMax * calcCoef) /
                 calcCoef;
    // norm = constrain(norm, toMin, toMax);
    Serial.print(norm);
    Serial.print(" ");
    // uint16_t freq = pow(1000, norm);
    uint16_t freq = 1000 * pow(norm, 2);
    Serial.println(freq);

    M5.Beep.tone(freq, interval / 1000);
  }
}