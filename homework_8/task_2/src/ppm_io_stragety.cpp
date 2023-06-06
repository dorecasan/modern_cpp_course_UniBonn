#include "ppm_io_stragety.h"

namespace igg {
ImageData PpmIoStrategy::Read(const std::string &file_name) const {
  std::ifstream in(file_name, std::ios_base::in);
  if (!in) {
    return {0, 0, 0, {}};
  }

  // Read integers, if we read chars, we get 1 digit instead of the whole number
  std::string type;
  int rows = 0;
  int cols = 0;
  int max_val = 0;
  std::vector<Pixel> data;
  in >> type >> rows >> cols >> max_val;

  data.reserve(rows * cols);
  int red = 0, green = 0, blue = 0;
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      in >> red >> green >> blue;
      data.emplace_back(Pixel(red, green, blue));
    }
  }
  return {rows, cols, max_val, data};
}

bool PpmIoStrategy::Write(const std::string &file_name,
                          const ImageData &img) const {
  std::ofstream out(file_name);
  if (!out) {
    return false;
  }

  out << "P3" << std::endl;
  out << img.rows_ << " " << img.cols_ << std::endl;
  out << img.max_val_ << std::endl;
  for (int r = 0; r < img.rows_; ++r) {
    for (int c = 0; c < img.cols_; ++c) {
      out << img.data_[r * img.cols_ + c].red << " "
          << img.data_[r * img.cols_ + c].green << " "
          << img.data_[r * img.cols_ + c].blue;
    }
    out << std::endl;
  }
  return true;
}
} // namespace igg