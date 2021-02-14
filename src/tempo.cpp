#include "./tempo.hpp"

Tempo::Tempo() { volume = 8; }

void Tempo::Update(double value) {
  if (value <= 0.0 || value > 1.0) return;
  double coef_up = 0.5;
  double coef_down = 0.0005;
  float bpm_min = 60.0;
  float bpm_max = 400.0;
  int key_id_min = 20;
  int key_id_max = 40;

  double coef = value > avg_value_ ? coef_up : coef_down;
  avg_value_ = avg_value_ * (1.0 - coef) + value * coef;
  float bpm = mapF(avg_value_, 0.0, 1.0, bpm_min, bpm_max);
  unsigned long interval = 60000000.0 / bpm;

  static unsigned long prev_micros = micros();
  if (micros() < prev_micros + interval) return;
  prev_micros = micros();
  Frequency frequency;
  int key_id = (int)mapF(avg_value_, 0.0, 1.0, key_id_min, key_id_max);
  key_id += random(-4, 4);
  uint16_t freq = frequency.getMajorScale(key_id);
  playSineWave(freq, volume, 200);
}