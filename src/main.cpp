#define M5STACK_MPU6886

#include <M5Stack.h>

#include "./tempo.hpp"

Tempo TEMPO;

void setup() {
  M5.begin(false, false, false, false);
  M5.IMU.Init();
  M5.Speaker.begin();
  M5.Speaker.setVolume(10);
}

void loop() {
  M5.update();
  static bool beep_state = true;
  if (M5.BtnA.wasPressed()) {
    Serial.println("wasPressed");
    beep_state = !beep_state;
  }
  if (M5.BtnB.wasPressed()) {
    TEMPO.volume /= 2;
    TEMPO.volume = constrain(TEMPO.volume, 4, 100);
  }
  if (M5.BtnC.wasPressed()) {
    TEMPO.volume *= 2;
    TEMPO.volume = constrain(TEMPO.volume, 4, 100);
  }
  if (beep_state) {
    // float accX = 0.0;
    // float accY = 0.0;
    // float accZ = 0.0;
    // M5.IMU.getAccelData(&accX, &accY, &accZ);
    // float absAcc = sqrt(accX * accX + accY * accY + accZ * accZ);
    // absAcc /= 5.0;

    float gyro_x = 0.0;
    float gyro_y = 0.0;
    float gyro_z = 0.0;
    M5.IMU.getGyroData(&gyro_x, &gyro_y, &gyro_z);
    gyro_x += -13.1;
    gyro_y += 14.5;
    gyro_z += -15.0;
    float abs_gyro = sqrt(gyro_x * gyro_x + gyro_y * gyro_y + gyro_z * gyro_z);
    abs_gyro /= 360.0;
    abs_gyro = constrain(abs_gyro, 0.0, 1.0);

    TEMPO.Update(abs_gyro);
  }
}