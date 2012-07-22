#include <iostream>
#include <iomanip>
#include "card_detector.hh"
#include "carddb.hh"

using namespace std;
using namespace rftgscore;

int main(int argc, char** argv) {
    cout << "rftgscore - by Viktor Larsson\n\n";
    
    if(argc == 3 && string(argv[1]) == "features") {
        CardDetector detector;

        if(atoi(argv[2]) & 1) detector.generate_feature_database("assets/base", "data/base");
        if(atoi(argv[2]) & 2) detector.generate_feature_database("assets/tgs", "data/tgs");
        if(atoi(argv[2]) & 4) detector.generate_feature_database("assets/rvi", "data/rvi");
        if(atoi(argv[2]) & 8) detector.generate_feature_database("assets/bow", "data/bow");

        cout << "Generated feature database";
        return 0;
    }

    if(argc == 4 && string(argv[1]) == "detect" ) {
        cv::Mat image = cv::imread(argv[3]);

        CardDetector detector;

        vector<string> paths;
        if(atoi(argv[2]) & 1) paths.push_back("data/base");
        if(atoi(argv[2]) & 2) paths.push_back("data/tgs");
        if(atoi(argv[2]) & 4) paths.push_back("data/rvi");
        if(atoi(argv[2]) & 8) paths.push_back("data/bow");          
      
        // TODO error handling
        vector<int> card_ids = detector.detect_cards(image, paths);

        CardDatabase db;
        if(atoi(argv[2]) & 1) db.load_cards("data/base.csv");
        if(atoi(argv[2]) & 2) db.load_cards("data/tgs.csv");

        // TODO support exps

        vector<Card> tableau;
        
        for(auto it = begin(card_ids); it != end(card_ids); ++it) {
            try {
                Card c = db.find_by_id(*it);
                tableau.push_back(c);
            } catch(CardNotFoundException &e) {
                cout << "ERROR: Card with ID=" << *it << " does not exist in database.\n";
            }
        }

        for(auto it = begin(tableau); it != end(tableau); ++it) {
            cout << left << setw(93) << it->to_string() << it->score(tableau) << "\n";
        }

        cout << "\nTABLEAU SCORE: " << score_tableau(tableau) << "\n";        

        return 0;
    }

    cout << "Available commands:\n";
    cout << left << setw(25) << "  features [exp]";
    cout << "generates the feature database.\n";
    cout << left << setw(25) << "  detect [exp] [image]";
    cout << "performs card detection and scoring.\n";    
    cout << "Available expansions are:\n";
    cout << "base  1\n";
    cout << "tgs   2\n";
    cout << "rvi   4\n";
    cout << "bow   8\n";       
    return 0;
}
