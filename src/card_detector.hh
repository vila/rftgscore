#ifndef CARD_DETECTOR_H
#define CARD_DETECTOR_H

#include <opencv2/opencv.hpp>

#include <vector>
#include <memory>
#include <string>

namespace rftgscore {

class CardDetector {
public:
    CardDetector();
    std::vector<int> detect_cards(cv::Mat image, const std::vector<std::string>& feature_paths);
    void generate_feature_database(const std::string& in_path, const std::string& out_path);

private:
    static const int MAX_CARD_FEATURES = 100;
    static const int REQUIRED_MATCHES = 5;
    
private:
    std::unique_ptr<cv::FeatureDetector> detector;
    std::unique_ptr<cv::DescriptorExtractor> extractor;
};

}
#endif /* CARD_DETECTOR_H */
