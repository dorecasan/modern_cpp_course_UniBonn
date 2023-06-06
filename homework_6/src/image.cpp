#include "image.h"

igg::Image::Image() : rows_(0), cols_(0){};
igg::Image::Image(int rows, int cols) : rows_(rows), cols_(cols) {
  data_.resize(rows_ * cols_);
};
const int &igg::Image::at(int row, int col) const {
  return data_[row * cols_ + col];
}
int &igg::Image::at(int row, int col) { return data_[row * cols_ + col]; }
int igg::Image::rows() const { return rows_; };
int igg::Image::cols() const { return cols_; };

bool igg::Image::FillFromPgm(const std::string &file_name) {
  igg::io_tools::ImageData img = igg::io_tools::ReadFromPgm(file_name);
  if (img.data.empty() || img.cols == 0 || img.rows == 0) {
    return false;
  }
  data_.clear();
  for (const auto &d : img.data) {
    data_.emplace_back(d);
  }
  rows_ = img.rows;
  cols_ = img.cols;
  return true;
};
void igg::Image::WriteToPgm(const std::string &file_name) {
  igg::io_tools::ImageData img_data;
  img_data.rows = rows();
  img_data.cols = cols();
  img_data.max_val = *std::max_element(data_.begin(), data_.end());
  img_data.data.resize(img_data.rows * img_data.cols);
  img_data.data.insert(img_data.data.begin(), data_.begin(), data_.end());
  igg::io_tools::WriteToPgm(img_data, file_name);
};

std::vector<float> igg::Image::ComputeHistogram(int bins) const {
  int maxValue = 255;
  std::vector<int> hist(bins, 0);
  std::vector<float> normHist(bins, 0.0f);
  int numData = rows() * cols();
  for (int i = 0; i < numData; i++) {
    int idx = data_[i] * bins / (maxValue + 1);
    hist[idx]++;
  }
  if (numData != 0) {
    for (int i = 0; i < bins; i++) {
      normHist[i] = static_cast<float>(hist[i]) / numData;
    }
  }
  return normHist;
}

void igg::Image::DownScale(int scale) {
  if (scale <= 0) {
    std::cout << " Invalid scale value";
  }
  int rows = rows_ / scale;
  int cols = cols_ / scale;
  std::vector<int> data(rows * cols, 0);
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

void igg::Image::UpScale(int scale) {
  if (scale <= 0) {
    std::cout << " Invalid scale value";
  }
  int rows = rows_ * scale;
  int cols = cols_ * scale;
  std::vector<int> data(rows * cols, 0);
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