#pragma once

#include <cstdint>
#include <vector>

class Bitmap {
 public:
  struct Pixel {
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
  };

  static void WriteToFile(
      const std::vector<std::vector<Bitmap::Pixel>>& pixels);
};
