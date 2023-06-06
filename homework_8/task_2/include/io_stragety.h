#pragma once
#include "utils.h"
#include <fstream>
#include <iostream>
#include <string>

namespace igg {
class IoStragety {
public:
  virtual ImageData Read(const std::string &file_name) const = 0;
  virtual bool Write(const std::string &file_name,
                     const ImageData &img) const = 0;
};
}; // namespace igg