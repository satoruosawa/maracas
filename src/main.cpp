#define M5STACK_MPU6886

#include <M5Stack.h>

#include "./tempo.hpp"

Tempo tempo;

void setup() {
  M5.begin(false, false, false, false);
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
  if (M5.BtnB.wasPressed()) {
    tempo.volume /= 2;
    tempo.volume = constrain(tempo.volume, 4, 100);
  }
  if (M5.BtnC.wasPressed()) {
    tempo.volume *= 2;
    tempo.volume = constrain(tempo.volume, 4, 100);
  }
  if (beepState) {
    // float accX = 0.0;
    // float accY = 0.0;
    // float accZ = 0.0;
    // M5.IMU.getAccelData(&accX, &accY, &accZ);
    // float absAcc = sqrt(accX * accX + accY * accY + accZ * accZ);
    // absAcc /= 5.0;

    float gyroX = 0.0;
    float gyroY = 0.0;
    float gyroZ = 0.0;
    M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
    gyroX += -13.1;
    gyroY += 14.5;
    gyroZ += -15.0;
    float absGyro = sqrt(gyroX * gyroX + gyroY * gyroY + gyroZ * gyroZ);
    absGyro /= 360.0;
    absGyro = constrain(absGyro, 0.0, 1.0);

    tempo.Update(absGyro);
  }
}