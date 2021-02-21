#define M5STACK_MPU6886

#include <M5Stack.h>

#include "./tempo.hpp"

#define lerp(from, to, coef) ((from) * (1.0 - (coef)) + (to) * (coef))

Tempo TEMPO;
float GYRO_X_AVG = 0.0;
float GYRO_Y_AVG = 0.0;
float GYRO_Z_AVG = 0.0;
float AVG_COEF = 0.1;

void setup() {
  M5.begin(false, false, false, false);  // LCD, SD, Serial, I2C
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
    GYRO_X_AVG = lerp(GYRO_X_AVG, gyro_x, AVG_COEF);
    GYRO_Y_AVG = lerp(GYRO_Y_AVG, gyro_y, AVG_COEF);
    GYRO_Z_AVG = lerp(GYRO_Z_AVG, gyro_z, AVG_COEF);

    float gyro_x_diff = GYRO_X_AVG - gyro_x;
    float gyro_y_diff = GYRO_Y_AVG - gyro_y;
    float gyro_z_diff = GYRO_Z_AVG - gyro_z;
    float abs_gyro =
        sqrt(gyro_x_diff * gyro_x_diff + gyro_y_diff * gyro_y_diff +
             gyro_z_diff * gyro_z_diff);
    abs_gyro /= 360.0;
    abs_gyro = constrain(abs_gyro, 0.0, 1.0);

    TEMPO.Update(abs_gyro);
  }
}