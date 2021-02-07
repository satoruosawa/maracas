#ifndef SINE_WAVE_HPP_
#define SINE_WAVE_HPP_

#include <M5Stack.h>

void playSineWave(uint16_t frequency, uint32_t durationMS);
void playSineWave(uint16_t frequency, uint8_t volume, uint32_t durationMS);

#endif  // SINE_WAVE_HPP_