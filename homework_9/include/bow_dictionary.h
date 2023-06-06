#pragma once
#include "kmeans.h"

namespace ipb {
class BowDictionary {
public:
  BowDictionary(const BowDictionary &) = delete;
  void operator=(const BowDictionary &) = delete;
  BowDictionary(const BowDictionary &&) = delete;
  void operator=(const BowDictionary &&) = delete;

  static BowDictionary &GetInstance() {
    static BowDictionary instance;
    return instance;
  };

  cv::Mat vocabulary() const { return this->codeBook_; }

  void set_vocabulary(const cv::Mat &vocab) { this->codeBook_ = vocab; }
  void build(int n_iters, int size, const std::vector<cv::Mat> &descriptors);
  bool empty(const std::vector<cv::Mat> &descriptors) const {
    return !(descriptors.size() > 0);
  };
  bool empty() const { return this->codeBook_.rows == 0; }
  int size() const { return this->codeBook_.rows; };

private:
  BowDictionary() = default;
  ~BowDictionary() = default;
  cv::Mat codeBook_;
};

}; // namespace ipb
