#include <iostream>
#include <iomanip>
#include "card_detector.hh"
#include "carddb.hh"

using namespace std;
using namespace rftgscore;

int main(int argc, char** argv) {
    cout << "rftgscore\n";

    CardDetector detector;
    
    if(argc == 2 && string(argv[1]) == "features") {
        detector.generate_feature_database("assets/base", "data/base");

        cout << "Generated feature database";
    }


    if(argc == 3) {
        cout << "usage: rftgscore [exp] [imagefile]\n";
        cout << "exps: 1 base\n";
        cout << "      2 tgs\n";
        cout << "      4 rvi\n";
        cout << "      8 bow\n";

        cv::Mat image = cv::imread(argv[2]);
        
        // TODO support exp and error handling
        vector<int> card_ids = detector.detect_cards(image, "data/base");

        CardDatabase db;
        db.load_cards("data/base.csv");
        // TODO load exps

        vector<Card> tableau;
        
        for(auto it = begin(card_ids); it != end(card_ids); ++it) {
            try {
                Card c = db.find_by_id(*it);
                tableau.push_back(c);
                cout << setw(70) << c.to_string() << " SCORE: " << c.score(tableau) << "\n";
            } catch(CardNotFoundException &e) {
                cout << "ERROR: Card with ID=" << *it << " does not exist in database.\n";
            }
        }

        cout << "\nTABLEAU SCORE: " << score_tableau(tableau) << "\n";        

        return 0;
    }

    return 0;
}
