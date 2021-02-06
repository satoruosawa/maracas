#ifndef TEMPO_HPP_
#define TEMPO_HPP_

#include <M5StickCPlus.h>

class Tempo {
 public:
  Tempo();
  void Update(float value);

 private:
  float bpm;
  float avgValue;
};

#endif  // TEMPO_HPP_
