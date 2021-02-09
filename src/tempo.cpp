#include "./tempo.hpp"

Tempo::Tempo() {}

void Tempo::Update(float value) {
  float coefUp = 0.5;
  float coefDown = 0.002;
  float valueToBpm = 120.0;
  float valueToFreq = 240.0;

  float coef = value > avgValue ? coefUp : coefDown;
  avgValue = avgValue * (1.0 - coef) + value * coef;
  float bpm = avgValue * valueToBpm;
  unsigned long interval = 60000000.0 / bpm;
  static unsigned long prevMicros = micros();
  if (micros() < prevMicros + interval) return;
  prevMicros = micros();
  float freq = avgValue * valueToFreq;
  freq = constrain(freq, 10.0, 1000.0);
  playSineWave(freq, 4, 100);
}