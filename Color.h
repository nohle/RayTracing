#pragma once

#include <cstdint>

class Color {
 public:
  Color();
  Color(uint8_t red, uint8_t green, uint8_t blue);
  ~Color();

  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t blue = 0;
  ;
};
