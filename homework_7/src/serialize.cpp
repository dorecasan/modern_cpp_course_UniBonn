#include "serialize.hpp"
#include <fstream>

void ipb::serialization::Serialize(const cv::Mat &m,
                                   const std::string &filename) {
  std::ofstream out(filename, std::ios_base::out | std::ios_base::binary);
  int rows = m.rows;
  int cols = m.cols;
  int channels = m.channels();
  int element_type = m.type();
  out.write(reinterpret_cast<char *>(&rows), sizeof(rows));
  out.write(reinterpret_cast<char *>(&cols), sizeof(cols));
  out.write(reinterpret_cast<char *>(&channels), sizeof(channels));
  out.write(reinterpret_cast<char *>(&element_type), sizeof(element_type));
  out.write(reinterpret_cast<char *>(m.data),
            rows * cols * channels * CV_ELEM_SIZE(element_type));
}

cv::Mat ipb::serialization::Deserialize(const std::string &filename) {
  std::ifstream in(filename, std::ios_base::in | std::ios_base::binary);
  int rows, cols, channels, element_type;
  in.read(reinterpret_cast<char *>(&rows), sizeof(rows));
  in.read(reinterpret_cast<char *>(&cols), sizeof(cols));
  in.read(reinterpret_cast<char *>(&channels), sizeof(channels));
  in.read(reinterpret_cast<char *>(&element_type), sizeof(element_type));
  cv::Mat m(rows, cols, element_type);
  in.read(reinterpret_cast<char *>(m.data),
          rows * cols * channels * CV_ELEM_SIZE(element_type));
  return m;
}
