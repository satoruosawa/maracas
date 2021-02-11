#include "./sine-wave.hpp"

void playSineWave(uint16_t frequency, uint32_t duration_ms) {
  uint8_t wave[1000];
  float sample_rate = 20000.0;
  float delta_phase = 2.0 * 3.14159 / sample_rate * float(frequency);
  float phase = 0;
  for (int i = 0; i < 1000; i++) {
    wave[i] = 127 - 126 * cos(phase);
    phase += delta_phase;
  }
  wave[999] = 0;
  int remains = duration_ms;
  for (int i = 0; i < duration_ms; i += 200) {
    if (remains < 200) {
      wave[remains * 999 / 200] = 0;
    }
    M5.Speaker.playMusic(wave, sample_rate);
    remains -= 200;
  }
}

void playSineWave(uint16_t frequency, uint8_t volume, uint32_t duration_ms) {
  uint8_t wave[1000];
  float sample_rate = 20000.0;
  float delta_phase = 2.0 * 3.14159 / sample_rate * float(frequency);
  float phase = 0;
  for (int i = 0; i < 1000; i++) {
    wave[i] = volume * (1 - cos(phase)) / 2;
    wave[i] = constrain(wave[i], 1, 255);
    phase += delta_phase;
  }
  wave[999] = 0;
  int remains = duration_ms;
  for (int i = 0; i < duration_ms; i += 200) {
    if (remains < 200) {
      wave[remains * 999 / 200] = 0;
    }
    M5.Speaker.playMusic(wave, (uint16_t)sample_rate);
    remains -= 200;
  }
}
