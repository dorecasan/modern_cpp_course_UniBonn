#pragma once

#include "io_stragety.h"
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace igg {
class Image {
public:
  Image() = default;
  Image(int rows, int cols);
  const Pixel &at(int row, int col) const { return data_[row * cols_ + col]; };
  Pixel &at(int row, int col) { return data_[row * cols_ + col]; };
  int rows() const { return rows_; };
  int cols() const { return cols_; };
  bool ReadFromDisk(const std::string &file_name);
  void WriteToDisk(const std::string &file_name);
  void DownScale(int scale);
  void UpScale(int scale);
  void SetIoStrategy(std::shared_ptr<IoStragety> stragety_ptr) {
    io_stragety_ = std::move(stragety_ptr);
  }

private:
  int rows_ = 0;
  int cols_ = 0;
  std::vector<Pixel> data_;
  std::shared_ptr<IoStragety> io_stragety_ = nullptr;
};
} // namespace igg