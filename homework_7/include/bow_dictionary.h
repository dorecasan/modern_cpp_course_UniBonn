#ifndef BOWDIC_HPP_
#define BOWDIC_HPP_

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

  int max_iterations() const { return max_iters_; };
  int size() const { return num_centroids_; };
  int total_features() const;
  cv::Mat vocabulary() const { return this->codeBook_; }
  std::vector<cv::Mat> descriptors() const { return this->descriptors_; }
  bool empty() const { return this->codeBook_.rows == 0; }

  void set_max_iterations(int iter_) { this->max_iters_ = iter_; };
  void set_size(int n);
  void set_descriptors(const std::vector<cv::Mat> &descriptors_);
  void set_params(int n_iters, int size,
                  const std::vector<cv::Mat> &descriptors);

private:
  BowDictionary() = default;
  ~BowDictionary() = default;
  int max_iters_;
  int num_words_;
  int num_centroids_;
  std::vector<cv::Mat> descriptors_;
  cv::Mat codeBook_;
};

}; // namespace ipb

#endif