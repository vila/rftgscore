#ifndef CARDDB_H
#define CARDDB_H

#include "card.hh"
#include <vector>
#include <stdexcept>

namespace rftgscore {

class CardNotFoundException : public std::runtime_error {
public:
    CardNotFoundException(const std::string& msg = "") : runtime_error(msg) {}
};

class CardDatabase {
public:
    // returns the number of cards loaded
    int load_cards(const std::string& filename);

    Card find_by_name(std::string name);
    Card find_by_id(int id);

private:
    std::vector<Card> cards;
};

}

#endif /* CARDDB_H */
