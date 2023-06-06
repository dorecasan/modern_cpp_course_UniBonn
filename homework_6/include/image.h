#include "../io_tools/io_tools.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
namespace igg {
class Image {
public:
  Image();
  Image(int rows, int cols);
  const int& at(int row, int col) const;
  int &at(int row, int col);
  int rows() const;
  int cols() const;
  bool FillFromPgm(const std::string &file_name);
  void WriteToPgm(const std::string &file_name);
  std::vector<float> ComputeHistogram(int bins) const;
  void DownScale(int scale);
  void UpScale(int scale);
private:
  int rows_;
  int cols_;
  std::vector<int> data_;
};
}