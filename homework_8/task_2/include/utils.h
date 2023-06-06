#pragma once

#include <cstddef>
#include <vector>

namespace igg {
struct Pixel {
  int red;
  int green;
  int blue;
  Pixel(int r, int g, int b) {
    red = r;
    green = g;
    blue = b;
  }
};

struct ImageData {
  int rows_;
  int cols_;
  int max_val_;
  std::vector<Pixel> data_;
};
} // namespace igg