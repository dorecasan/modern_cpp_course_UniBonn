#include "kmeans.h"

namespace ipb {

std::vector<cv::Mat> initialCentroids(const std::vector<cv::Mat> &descriptors,
                                      int k) {
  std::vector<cv::Mat> centroids;
  centroids.reserve(k);

  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<int> distribution(0, descriptors.size() - 1);

  for (int i = 0; i < k; ++i) {
    centroids.push_back(descriptors[distribution(generator)].clone());
  }
  return centroids;
}

void distributeCentroids(const std::vector<cv::Mat> &descriptors,
                         const std::vector<cv::Mat> &centroids,
                         std::map<int, std::vector<int>> &centroid_indices) {
  for (int d = 0; d < descriptors.size(); d++) {
    cv::Mat descriptor = descriptors[d];
    double minDis = std::numeric_limits<double>::max();
    int centroid_idx = -1;
    for (int i = 0; i < centroids.size(); i++) {
      double distance = cv::norm(descriptor, centroids[i], cv::NORM_L2);
      if (distance < minDis) {
        minDis = distance;
        centroid_idx = i;
      }
    }
    centroid_indices[centroid_idx].push_back(d);
  }
}

void updateCentroids(std::vector<cv::Mat> &centroids,
                     std::map<int, std::vector<int>> &centroid_indices,
                     const std::vector<cv::Mat> &descriptors) {
  centroids = initialCentroids(descriptors, centroids.size());
  for (int i = 0; i < centroids.size(); i++) {
    cv::Mat meanCluster = cv::Mat::zeros(
        descriptors[0].rows, descriptors[0].cols, descriptors[0].type());
    if (centroid_indices[i].size()) {
      for (int idx : centroid_indices[i]) {
        meanCluster += descriptors[idx];
      }
      meanCluster /= static_cast<float>(centroid_indices[i].size());
      centroids[i] = meanCluster;
    }
  }
}

cv::Mat kMeans(const std::vector<cv::Mat> &descriptors, int k, int max_iter) {

  std::vector<cv::Mat> centroids = initialCentroids(descriptors, k);

  for (int iter = 0; iter < max_iter; iter++) {
    std::map<int, std::vector<int>> centroid_indices;
    distributeCentroids(descriptors, centroids, centroid_indices);

    updateCentroids(centroids, centroid_indices, descriptors);
  }

  cv::Mat centers(k, centroids[0].cols, centroids[0].type());
  for (int i = 0; i < k; i++) {
    centroids[i].copyTo(centers.row(i));
  }
  return centers;
}

} // namespace ipb