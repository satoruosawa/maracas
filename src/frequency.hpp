#ifndef FREQUENCY_HPP_
#define FREQUENCY_HPP_

#include <M5Stack.h>

#include "./frequency-list.hpp"

class Frequency {
 public:
  Frequency();
  uint16_t get12ET(int id);
  uint16_t getMajorScale(int id);
};

#endif  // FREQUENCY_HPP_
