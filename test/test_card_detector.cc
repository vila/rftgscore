#include "card_detector.hh"
#include "carddb.hh"
#include "misc.hh"
#include "gtest/gtest.h"

#include <vector>
#include <algorithm>
#include <string>

using namespace rftgscore;
using namespace std;





class CardDetectorTest : public ::testing::Test {
protected:
    CardDetector detector;
    CardDatabase db;

    virtual void SetUp() {
        // make sure that the features database is generated
        if(list_directory("data/base").size() == 0)
             detector.generate_feature_database("assets/base", "data/base");
        if(list_directory("data/tgs").size() == 0)
            detector.generate_feature_database("assets/tgs", "data/tgs");
        if(list_directory("data/rvi").size() == 0)
            detector.generate_feature_database("assets/rvi", "data/rvi");
        if(list_directory("data/bow").size() == 0)
            detector.generate_feature_database("assets/bow", "data/bow");

        db.load_cards("data/base.csv");
        db.load_cards("data/tgs.csv");
        db.load_cards("data/rvi.csv");
        db.load_cards("data/bow.csv");
    }

    bool compare_tableau(vector<string> expected, vector<int> detected) {
        if(expected.size() != detected.size())
            return false;

        vector<int> expected_ids;
        transform(begin(expected), end(expected), back_inserter(expected_ids),
                  [&](string& s){ return db.find_by_name(s).id; });

        sort(begin(expected_ids), end(expected_ids));
        sort(begin(detected), end(detected));

        return equal(begin(expected_ids), end(expected_ids), begin(detected));
    }

};

TEST_F(CardDetectorTest, base_tableau1) {
    vector<string> expected = {
        "Alpha Centauri", "Expanding Colony", "Merchant World",
        "Replicant Robots", "Expedition Force", "Spice World",
        "Pirate World", "Deficit Spending", "Free Trade Association",
        "Gem World", "Prosperous World"
    };

    cv::Mat image = cv::imread("test/assets/base_tableau1.jpg");

    vector<int> detected = detector.detect_cards(image, {"data/base"});
    ASSERT_TRUE(compare_tableau(expected, detected));
}

TEST_F(CardDetectorTest, base_tgs1) {
    vector<string> expected = {
        "Alien Toy Shop", "Alien Robot Sentry", "Damaged Alien Factory",
        "Investment Credits","Public Works", "Imperium Armaments World",
        "Deserted Alien Colony", "Drop Ships", "Improved Logistics",
        "Replicant Robots", "Alien Rosetta Stone World",
        "Alien Tech Institute", "Blaster Gem Mines"
    };

    cv::Mat image = cv::imread("test/assets/tgs_tableau1.jpg");

    vector<int> detected = detector.detect_cards(image, {"data/base", "data/tgs"});
    ASSERT_TRUE(compare_tableau(expected, detected));
}

TEST_F(CardDetectorTest, base_tgs2) {
    vector<string> expected = {
        "Pre-sentient race", "Ancient Race",
        "The last of the Uplift Gnarssh", "Aquatic Uplift Race",
        "Export Duties", "Galactic Federation", "Contact Specialist",
        "Pan-Galactic League", "Genetics Lab", "Terraforming Guild"
    };

    cv::Mat image = cv::imread("test/assets/tgs_tableau2.jpg");

    vector<int> detected = detector.detect_cards(image, {"data/base", "data/tgs"});
    ASSERT_TRUE(compare_tableau(expected, detected));
}
