#include "card.hh"
#include "gtest/gtest.h"
#include "carddb.hh"

#include <vector>

using namespace rftgscore;
using namespace std;

TEST(Card, ScoreSimpleTableauNoSixDev) {
    CardDatabase db;
    db.load_cards("test/assets/simple_db.csv");
    
    vector<Card> tableau;
    tableau.push_back(db.find_by_name("Colony Ship"));
    tableau.push_back(db.find_by_name("Consumer Markets"));
    tableau.push_back(db.find_by_name("Artist Colony"));
    tableau.push_back(db.find_by_name("Rebel Warrior Race"));
    tableau.push_back(db.find_by_name("Epsilon Eridani"));

    ASSERT_EQ(8, score_tableau(tableau));
}

TEST(Card, SixDevFreeTradeAssoc) {
    CardDatabase db;
    db.load_cards("test/assets/six_dev_db.csv");

    Card c = db.find_by_name("Free Trade Association");

    vector<Card> tableau;
    tableau.push_back(c);
    ASSERT_EQ(0, c.score(tableau));

    tableau.push_back(db.find_by_name("Consumer Markets"));
    ASSERT_EQ(2, c.score(tableau));

    tableau.push_back(db.find_by_name("Expanding Colony"));
    ASSERT_EQ(4, c.score(tableau));

    tableau.push_back(db.find_by_name("Artist Colony"));
    ASSERT_EQ(6, c.score(tableau));
    
    tableau.push_back(db.find_by_name("Star Nomad Lair"));
    ASSERT_EQ(7, c.score(tableau));
        
    tableau.push_back(db.find_by_name("Earth's Lost Colony"));
    ASSERT_EQ(9, c.score(tableau));

}

TEST(Card, SixDevGalacticImperium) {
  CardDatabase db;
    db.load_cards("test/assets/six_dev_db.csv");

    Card c = db.find_by_name("Galactic Imperium");

    vector<Card> tableau;
    tableau.push_back(c);
    ASSERT_EQ(0, c.score(tableau));

    tableau.push_back(db.find_by_name("Artist Colony"));
    ASSERT_EQ(0, c.score(tableau));


    tableau.push_back(db.find_by_name("Rebel Miners"));
    ASSERT_EQ(2, c.score(tableau));

    tableau.push_back(db.find_by_name("Rebel Fuel Cache"));
    ASSERT_EQ(4, c.score(tableau));
    
    tableau.push_back(db.find_by_name("Star Nomad Lair"));
    ASSERT_EQ(5, c.score(tableau));
}


TEST(Card, SixDevAlienTechInstitute) {
  CardDatabase db;
    db.load_cards("test/assets/six_dev_db.csv");

    Card c = db.find_by_name("Alien Tech Institute");

    vector<Card> tableau;
    tableau.push_back(c);
    ASSERT_EQ(2, c.score(tableau));

    tableau.push_back(db.find_by_name("Lost Alien Battle Fleet"));
    ASSERT_EQ(5, c.score(tableau));

    tableau.push_back(db.find_by_name("Lost Alien Warship"));
    ASSERT_EQ(7, c.score(tableau));

    tableau.push_back(db.find_by_name("Alien Rosetta Stone World"));
    ASSERT_EQ(9, c.score(tableau));
    
    tableau.push_back(db.find_by_name("Artist Colony"));
    ASSERT_EQ(9, c.score(tableau));
}

// TODO test rest of six devs
