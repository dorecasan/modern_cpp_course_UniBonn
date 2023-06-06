#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
  float data[3] = {1, 2, 3};
  cv::Mat toan1(1, 3, CV_64F, data);
  std::cout << toan1.row(0).rows;
}