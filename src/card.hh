#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

namespace rftgscore {

class Card {
public:
    int score(const std::vector<Card> &tableau);
    std::string to_string();

    // unique id
    int id;
    // Card name (e.g. "Galactic Trendsetters", "Colony Ship", ...
    std::string name;
    // Type, 0 = development
    enum CardType {
        DEVELOPMENT             = 0,
        PLANET                  = 1,
        PLANET_NOVELTY          = 2,
        PLANET_NOVELTY_WINDFALL = 3,
        PLANET_RARE             = 4,
        PLANET_RARE_WINDFALL    = 5,
        PLANET_GENE             = 6,
        PLANET_GENE_WINDFALL    = 7,
        PLANET_ALIEN            = 8,
        PLANET_ALIEN_WINDFALL   = 9,
    } type;

    enum CardSubType {
        NONE     = 0,
        ALIEN    = 1,
        UPLIFT   = 2,
        REBEL    = 3,
        IMPERIUM = 4
    } sub_type;

    // If the planet is military (only used when type > 0)
    bool military;

    // cost or defence
    int cost;
    // vp value (0 for 6-developments)
    int value;

    static const int POWER_EXPLORE = 0x01;
    static const int POWER_DEVELOP = 0x02;
    static const int POWER_SETTLE  = 0x04;
    static const int POWER_TRADE   = 0x08;
    static const int POWER_CONSUME = 0x10;
    static const int POWER_PRODUCE = 0x20;

    // bitmap of which powers the card has
    int powers;

    // if the card has +military (can be negative and does not count specialized military)
    int increase_military;
};

int score_tableau(const std::vector<Card> &tableau);

}

#endif /* CARD_H */
