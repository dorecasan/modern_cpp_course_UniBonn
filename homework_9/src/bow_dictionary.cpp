#include "bow_dictionary.h"

namespace ipb {
void BowDictionary::build(int n_iters, int size,
                          const std::vector<cv::Mat> &descriptors) {
  this->codeBook_ = kMeans(descriptors, size, n_iters);
}
} // namespace ipb