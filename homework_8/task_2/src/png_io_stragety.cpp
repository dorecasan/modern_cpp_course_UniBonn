#include "png_io_stragety.h"

namespace igg {
ImageData PngIoStrategy::Read(const std::string &file_name) const {
  png::image<png::rgb_pixel> image(file_name,
                                   png::require_color_space<png::rgb_pixel>());
  ImageData out;
  out.rows_ = image.get_height();
  out.cols_ = image.get_width();
  out.max_val_ = 255;
  for (png::uint_32 y = 0; y < image.get_height(); ++y) {
    for (png::uint_32 x = 0; x < image.get_width(); ++x) {
      Pixel pix(image[y][x].red, image[y][x].green, image[y][x].blue);
      out.data_.emplace_back(pix);
    }
  }
  return out;
}

bool PngIoStrategy::Write(const std::string &file_name,
                          const ImageData &img) const {
  png::image<png::rgb_pixel> image(img.rows_, img.cols_);
  for (png::uint_32 i = 0; i < img.rows_; i++) {
    for (png::uint_32 j = 0; j < img.cols_; j++) {
      Pixel pix = img.data_[i * img.cols_ + j];
      image[i][j] = png::rgb_pixel(pix.red, pix.green, pix.blue);
    }
  }
  image.write(file_name);
  return true;
}
} // namespace igg