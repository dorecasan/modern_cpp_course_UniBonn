#pragma once
#include "io_stragety.h"
#include <png++/png.hpp>
namespace igg {
class PngIoStrategy : public IoStragety {
public:
  ImageData Read(const std::string &file_name) const override;
  bool Write(const std::string &file_name, const ImageData &img) const override;
};
}; // namespace igg