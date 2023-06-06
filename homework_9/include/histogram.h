#pragma once
#include "bow_dictionary.h"
#include <fstream>
namespace ipb {
class Histogram {
private:
  std::vector<int> data_;

public:
  Histogram() = default;
  Histogram(const std::vector<int> &data) { data_ = data; };
  Histogram(const cv::Mat &descriptors, BowDictionary &dictionary);

  void WriteToCSV(const std::string &file_name);
  static Histogram ReadFromCSV(const std::string &file_name);

  std::ostream &operator<<(std::ostream &out) const;

  int operator[](int idx) const { return data_[idx]; };
  int &operator[](int idx) { return data_[idx]; };
  friend std::ostream &operator<<(std::ostream &stream,
                                  const Histogram &histogram) {
    for (std::size_t i = 0; i < histogram.size(); ++i) {
      stream << histogram[i];
      if (i != histogram.size() - 1) {
        stream << ", ";
      }
    }
    return stream;
  }
  int size() const { return data_.size(); }
  bool empty() const { return !(data_.size() > 0); }
  std::vector<int> data() const { return data_; }

  std::vector<int>::const_iterator begin() const { return data_.cbegin(); }
  std::vector<int>::const_iterator end() const { return data_.cend(); }

  std::vector<int>::const_iterator cbegin() const { return data_.cbegin(); }
  std::vector<int>::const_iterator cend() const { return data_.cend(); }
};
}; // namespace ipb