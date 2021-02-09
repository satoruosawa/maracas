#include "./tempo.hpp"

Tempo::Tempo() { volume = 8; }

void Tempo::Update(double value) {
  if (value <= 0.0 || value > 1.0) return;
  double coefUp = 0.5;
  double coefDown = 0.0005;
  float valueToBpm = 400.0;
  float valueToFreq = 1000.0;

  double coef = value > avgValue ? coefUp : coefDown;
  avgValue = avgValue * (1.0 - coef) + value * coef;
  float bpm = avgValue * valueToBpm;
  unsigned long interval = 60000000.0 / bpm;

  static unsigned long prevMicros = micros();
  if (micros() < prevMicros + interval) return;
  prevMicros = micros();
  float freq = avgValue * valueToFreq;
  playSineWave(freq, volume, 100);
}