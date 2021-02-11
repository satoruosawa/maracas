#ifndef TEMPO_HPP_
#define TEMPO_HPP_

#include <M5Stack.h>

#include "./sine-wave.hpp"

class Tempo {
 public:
  Tempo();
  void Update(double value);
  uint8_t volume;

 private:
  double avg_value_;
};

#endif  // TEMPO_HPP_
