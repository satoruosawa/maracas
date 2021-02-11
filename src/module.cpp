#include "./module.hpp"

float mapF(float value, float from_min, float from_max, float to_min,
           float to_max) {
  return (value - from_min) * (to_max - to_min) / (from_max - from_min) +
         to_min;
}