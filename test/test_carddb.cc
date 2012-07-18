#include "gtest/gtest.h"
#include "card.hh"
#include "carddb.hh"

using namespace rftgscore;

TEST(CardDatabase, LoadNonExistentFile) {
    CardDatabase db;

    ASSERT_EQ(-1, db.load_cards("some_file_that_doesnt_exist.csv"));
}

TEST(CardDatabase, CorrectNumberCardsLoaded) {
    CardDatabase db;

    ASSERT_EQ(8, db.load_cards("test/assets/simple_db.csv"));
}

TEST(CardDatabase, FindNonExistentCard) {
    CardDatabase db;
    db.load_cards("test/assets/simple_db.csv");

    ASSERT_THROW(db.find_by_id(1234), CardNotFoundException);    
    ASSERT_THROW(db.find_by_name("somename"), CardNotFoundException);
}

TEST(CardDatabase, FindByName) {
    CardDatabase db;
    db.load_cards("test/assets/simple_db.csv");
    
    Card c;
    ASSERT_NO_THROW({
            c = db.find_by_name("Rebel Warrior Race");        
    });
    ASSERT_EQ(353882, c.id);
}

TEST(CardDatabase, FindById) {
    CardDatabase db;
    db.load_cards("test/assets/simple_db.csv");
    
    Card c;
    ASSERT_NO_THROW({
            c = db.find_by_id(356855);
            
    });
    ASSERT_EQ("ARTIST COLONY", c.name);
}
