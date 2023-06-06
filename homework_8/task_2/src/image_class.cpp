#include "image_class.h"
#include <iostream>

namespace igg {
Image::Image(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  data_.resize(rows * cols, Pixel(0, 0, 0));
}

void Image::DownScale(int scale) {
  if (scale <= 0) {
    std::cout << " Invalid scale value";
  }
  int rows = rows_ / scale;
  int cols = cols_ / scale;
  std::vector<Pixel> data(rows * cols, Pixel(0, 0, 0));
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int row_idx = i * scale;
      int col_idx = j * scale;
      data[i * rows + j] = this->at(row_idx, col_idx);
    }
  }
  rows_ = rows;
  cols_ = cols;
  data_ = std::move(data);
}

void Image::UpScale(int scale) {
  if (scale <= 0) {
    std::cout << " Invalid scale value";
  }
  int rows = rows_ * scale;
  int cols = cols_ * scale;
  std::vector<Pixel> data(rows * cols, Pixel(0, 0, 0));
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int row_idx = i / scale;
      int col_idx = j / scale;
      data[i * rows + j] = this->at(row_idx, col_idx);
    }
  }
  rows_ = rows;
  cols_ = cols;
  data_ = std::move(data);
}

bool Image::ReadFromDisk(const std::string &file_name) {
  if (io_stragety_ == nullptr) {
    exit(1);
  }
  ImageData img = io_stragety_->Read(file_name);
  rows_ = img.rows_;
  cols_ = img.cols_;
  data_ = img.data_;
  return true;
}

void Image::WriteToDisk(const std::string &file_name) {
  if (io_stragety_ == nullptr) {
    exit(1);
  }

  ImageData img;
  img.rows_ = rows_;
  img.cols_ = cols_;
  img.max_val_ = 255;
  img.data_ = data_;

  io_stragety_->Write(file_name, img);
}

} // namespace igg