#include "card_detector.hh"
#include <opencv2/opencv.hpp>

#include <vector>
#include <string>
#include <algorithm>
#include <memory>

#include "misc.hh"

using namespace std;
using namespace rftgscore;

CardDetector::CardDetector() {
    int minHessian = 400;

    detector = unique_ptr<cv::FeatureDetector>(new cv::SurfFeatureDetector(minHessian));
    extractor = unique_ptr<cv::DescriptorExtractor>(new cv::SurfDescriptorExtractor);
}


vector<int> CardDetector::detect_cards(cv::Mat image, const vector<string>& feature_paths) {  
    cv::cvtColor(image, image, CV_BGR2GRAY);
    cv::resize(image, image, cv::Size(), 0.5, 0.5);

    // find key points
    vector<cv::KeyPoint> keypoints;
    detector->detect(image, keypoints);
       
    // extract descriptors
    cv::Mat features;
    extractor->compute(image, keypoints, features);

    cv::BruteForceMatcher<cv::L2<float> > matcher;
    vector<int> found_cards;

    for(auto path = begin(feature_paths); path != end(feature_paths); ++path) {
        
        vector<string> files = list_directory(*path);

        for(auto it = begin(files); it != end(files); ++it) {
            cv::FileStorage fs(*path + "/" + *it, cv::FileStorage::READ);
            if(!fs.isOpened()) {
                cout << "Unable to open file " << *it << "\n";
                continue;
            }

            int id;
            cv::Mat card_features;
            fs["id"] >> id;
            fs["descriptors"] >> card_features;

            // we find the two best matches for each descriptor
            vector<vector<cv::DMatch>> matches;
            matcher.knnMatch(card_features, features, matches, 2);

       
            int num_matches = 0;
            for(auto it = begin(matches); it != end(matches); ++it) {
                // check if it is a good match
                if((*it)[0].distance < 0.6 * (*it)[1].distance && (*it)[0].distance < 0.15) {
                    num_matches++;
                }
            }
  
            if(num_matches >= REQUIRED_MATCHES)
                found_cards.push_back(id);
        }
    }
    return found_cards;
}

void CardDetector::generate_feature_database(const std::string& in_path,
                                             const std::string& out_path) {
   
    vector<string> files = list_directory(in_path);

    for(auto it = begin(files); it != end(files); ++it) {
        // parse card id from filename
        string str;
        copy(find_if(begin(*it), end(*it), [](char c){return isdigit(c) != 0;}),
             end(*it), back_inserter(str));
        int id = atoi(str.c_str());

        if(id == 0)
            continue;

        // load card image
        cv::Mat card_image = cv::imread(in_path + "/" + *it);
        if(card_image.empty()) {
            cout << "Unable to load image \"" << *it << "\"\n";
            continue;
        }

        cv::cvtColor(card_image, card_image, CV_BGR2GRAY);

        cv::resize(card_image, card_image, cv::Size(), 0.5, 0.5);

        // we need to mask out common image areas
        // we discard the leftmost 40% of the image, and 20% top
        // so that we mostly get points from the artwork
        cv::Mat mask = cv::Mat::zeros(card_image.size(), CV_8UC1);
        cv::rectangle(mask,
                      cv::Point(card_image.cols*0.4,card_image.rows*0.20),
                      cv::Point(card_image.cols, card_image.rows),
                      cv::Scalar(255), CV_FILLED);
        

        cout << "id:" << id << " ... ";
        
        // find keypoints
        vector<cv::KeyPoint> keypoints;
        detector->detect(card_image, keypoints, mask);
        cout << keypoints.size() << " points found ...";

        // only keep the MAX_CARD_FEATURES best points
        if(keypoints.size() > MAX_CARD_FEATURES) {
            nth_element(begin(keypoints), begin(keypoints)+MAX_CARD_FEATURES-1, end(keypoints),
                        [](cv::KeyPoint a, cv::KeyPoint b){return a.response > b.response;});
            keypoints.erase(begin(keypoints)+MAX_CARD_FEATURES, end(keypoints));
        }

        // extract descriptors
        cv::Mat features;
        extractor->compute(card_image, keypoints, features);

        cv::FileStorage fs(out_path + "/" + itos(id) + ".yml", cv::FileStorage::WRITE);
        fs << "id" << id;
        fs << "descriptors" << features;
        fs.release();

        cout << "done!\n";      
    }
}
