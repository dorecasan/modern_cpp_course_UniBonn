#include "bow_dictionary.h"

namespace ipb {
void BowDictionary::set_descriptors(const std::vector<cv::Mat> &descriptors) {
  std::vector<cv::Mat> all_descriptors;

  for (const auto &p : descriptors) {
    for (int i = 0; i < p.rows; i++) {
      all_descriptors.emplace_back(p.row(i));
    }
  }

  this->descriptors_ = all_descriptors;
};
int BowDictionary::total_features() const {
  int total = 0;
  for (const auto &p : this->descriptors_) {
    total += p.rows;
  }
  return total;
}
void BowDictionary::set_size(int n) {
  this->num_centroids_ = n;
  this->codeBook_ = cv::Mat::zeros(n, this->descriptors_[0].cols, CV_64F);
}
void BowDictionary::set_params(int n_iters, int size,
                               const std::vector<cv::Mat> &descriptors) {
  set_descriptors(descriptors);
  set_size(size);
  set_max_iterations(n_iters);
  this->codeBook_ = kMeans(descriptors, size, n_iters);
}
} // namespace ipb