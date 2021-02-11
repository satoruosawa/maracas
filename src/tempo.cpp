#include "./tempo.hpp"

Tempo::Tempo() { volume = 8; }

void Tempo::Update(double value) {
  if (value <= 0.0 || value > 1.0) return;
  double coef_up = 0.5;
  double coef_down = 0.0005;
  float value_to_bpm = 400.0;
  float value_to_freq = 1000.0;

  double coef = value > avg_value_ ? coef_up : coef_down;
  avg_value_ = avg_value_ * (1.0 - coef) + value * coef;
  float bpm = avg_value_ * value_to_bpm;
  unsigned long interval = 60000000.0 / bpm;

  static unsigned long prev_micros = micros();
  if (micros() < prev_micros + interval) return;
  prev_micros = micros();
  float freq = avg_value_ * value_to_freq;
  playSineWave(freq, volume, 100);
}