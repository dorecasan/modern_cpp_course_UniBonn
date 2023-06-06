#include "histogram.h"

namespace ipb {
Histogram::Histogram(const cv::Mat &descriptors, BowDictionary &dictionary) {
  if (descriptors.size().height == 0) {
    return;
  }
  data_.reserve(dictionary.size());
  for (int i = 0; i < data_.capacity(); i++) {
    data_.push_back(0);
  }
  static cv::flann::Index flann_index(dictionary.vocabulary(),
                                      cv::flann::KDTreeIndexParams(1));
  cv::Mat indices, distances;
  for (int i = 0; i < descriptors.rows; i++) {
    flann_index.knnSearch(descriptors.row(i), indices, distances,
                          dictionary.size(), cv::flann::SearchParams(32));
    data_[indices.at<int>(0, 0)] += 1;
  }
};

Histogram Histogram::ReadFromCSV(const std::string &file_name) {
  std::ifstream in(file_name, std::ios_base::in);
  std::vector<int> data;
  if (!in) {
    std::cout << "Error: Could not open the file";
  } else {
    std::string line;
    if (!std::getline(in, line)) {
      std::cout << "Error, the file is empty";
    } else {
      std::stringstream ss(line);
      std::string value;
      while (std::getline(ss, value, ',')) {
        data.emplace_back(std::stoi(value));
      }
    }
  }
  return Histogram(data);
};

void Histogram::WriteToCSV(const std::string &file_name) {
  std::ofstream out(file_name);
  if (!out) {
    std::cout << "Could not open the file";
  } else {
    for (const auto &d : data_) {
      out << d << ",";
    }
  }
  out.seekp(-1, std::ios_base::end);
  out << std::endl;
  out.close();
};
} // namespace ipb
