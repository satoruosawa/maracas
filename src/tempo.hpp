#ifndef TEMPO_HPP_
#define TEMPO_HPP_

#include <M5Stack.h>

#include "./sine-wave.hpp"

class Tempo {
 public:
  Tempo();
  void Update(float value);

 private:
  float avgValue;
};

#endif  // TEMPO_HPP_
