#include "convert_dataset.hpp"
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <tuple>

using cv::SiftDescriptorExtractor;
using cv::SiftFeatureDetector;

namespace fs = std::experimental::filesystem;
namespace ipb::serialization::sifts {

std::tuple<cv::Mat, std::vector<cv::KeyPoint>>
ComputeSifts(const std::string &file_name) {
  cv::Mat img = cv::imread(file_name);
  std::vector<cv::KeyPoint> keypoints;
  cv::Mat descriptors;

  auto detector = SiftFeatureDetector::create();
  detector->detect(img, keypoints);

  auto extractor = SiftDescriptorExtractor::create();
  extractor->compute(img, keypoints, descriptors);

  return std::make_tuple(descriptors, keypoints);
}
void ConvertDataset(const std::experimental::filesystem::path &img_path) {
  fs::path bin_dir = "bin";
  fs::create_directory(img_path.parent_path() / bin_dir);
  for (auto const &p : fs::directory_iterator(img_path)) {
    if (p.path().extension() == ".png") {
      auto sifts = ComputeSifts(p.path());
      cv::Mat descriptors = std::get<0>(sifts);
      fs::path binFile = p;
      binFile.replace_extension(".bin");
      fs::path outputFile = img_path.parent_path() / bin_dir / binFile;
      Serialize(descriptors, outputFile.filename());
    }
  }
}

std::vector<cv::Mat>
LoadDataset(const std::experimental::filesystem::path &bin_path) {
  std::vector<cv::Mat> descriptors;
  for (auto const &p : fs::directory_iterator(bin_path)) {
    if (p.path().extension() == ".bin") {
      cv::Mat descriptor = Deserialize(p.path());
      descriptors.push_back(descriptor);
    }
  }
  return descriptors;
}
}; // namespace ipb::serialization::sifts
