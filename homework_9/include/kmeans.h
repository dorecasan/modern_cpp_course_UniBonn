#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <map>
#include <opencv2/opencv.hpp>
#include <random>
#include <vector>
namespace ipb {

std::vector<cv::Mat> initialCentroids(const std::vector<cv::Mat> &descriptors,
                                      int k);

void distributeCentroids(const std::vector<cv::Mat> &descriptors,
                         const std::vector<cv::Mat> &centroids,
                         std::map<int, std::vector<int>> &centroid_indices);
void updateCentroids(std::vector<cv::Mat> &centroids,
                     std::map<int, std::vector<int>> &centroid_indices,
                     const std::vector<cv::Mat> &descriptors);

cv::Mat kMeans(const std::vector<cv::Mat> &descriptors, int k,
               int max_iter); // namespace ipb
} // namespace ipb