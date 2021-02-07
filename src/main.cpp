#define M5STACK_MPU6886

#include <M5Stack.h>

#include "./tempo.hpp"

Tempo tempo;

void setup() {
  M5.begin();
  M5.IMU.Init();
  M5.Speaker.begin();
  M5.Speaker.setVolume(10);
}

void loop() {
  M5.update();
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
    float absAcc = pow(accX * accX + accY * accY + accZ * accZ, 1.0 / 3.0);
    tempo.Update(absAcc);
  }
}