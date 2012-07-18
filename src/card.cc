#include "card.hh"

#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace rftgscore;
using namespace std;

static int score_free_trade_association(const vector<Card> &tableau);
static int score_galactic_imperium(const vector<Card> &tableau);
static int score_alien_tech_institute(const vector<Card> &tableau);
static int score_galactic_federation(const vector<Card> &tableau);
static int score_galactic_renaissance(const vector<Card> &tableau);
static int score_galactic_survey_seti(const vector<Card> &tableau);
static int score_merchant_guild(const vector<Card> &tableau);
static int score_mining_league(const vector<Card> &tableau);
static int score_new_economy(const vector<Card> &tableau);
static int score_new_galactic_order(const vector<Card> &tableau);
static int score_pan_galactic_league(const vector<Card> &tableau);
static int score_trade_league(const vector<Card> &tableau);




int rftgscore::score_tableau(const vector<Card> &tableau) {
    int score = 0;

    for_each(begin(tableau), end(tableau),
             [&](Card c) { score += c.score(tableau); });

    return score;
}

int Card::score(const vector<Card> &tableau) {
    int score = value;

    // TODO: handle all 6-developments
    switch(id) {
    case 356848: score = score_free_trade_association(tableau); break;
    case 356852: score = score_galactic_imperium(tableau); break;
    case 354518: score = score_alien_tech_institute(tableau); break;
    case 356847: score = score_galactic_federation(tableau); break;
    case 340468: score = score_galactic_renaissance(tableau); break;
    case 354517: score = score_galactic_survey_seti(tableau); break;
    case 341376: score = score_merchant_guild(tableau); break;
    case 341710: score = score_mining_league(tableau); break;
    case 340466: score = score_new_economy(tableau); break;
    case 340904: score = score_new_galactic_order(tableau); break;
    case 356846: score = score_pan_galactic_league(tableau); break;
    case 340448: score = score_trade_league(tableau); break;
    }

    return score;
}

std::string Card::to_string() {
    stringstream ss;

    ss << id << ": \"" << name;
    ss << "\"  (" << cost << "/" << value << ") ";

    if(military) {
        ss << "Mil. ";
    }

    switch(type) {
    case CardType::DEVELOPMENT:              ss << "Development"; break;
    case CardType::PLANET:                   ss << "Planet"; break;
    case CardType::PLANET_NOVELTY:           ss << "Planet (Novelty)"; break;
    case CardType::PLANET_NOVELTY_WINDFALL:  ss << "Planet (Novelty/Windfall)"; break;
    case CardType::PLANET_RARE:              ss << "Planet (Rare)"; break;
    case CardType::PLANET_RARE_WINDFALL:     ss << "Planet (Rare/Windfall)"; break;
    case CardType::PLANET_GENE:              ss << "Planet (Gene)"; break;
    case CardType::PLANET_GENE_WINDFALL:     ss << "Planet (Gene/Windfall)"; break;
    case CardType::PLANET_ALIEN:             ss << "Planet (Alien)"; break;
    case CardType::PLANET_ALIEN_WINDFALL:    ss << "Planet (Alien/Windfall)"; break;
    }
        

    switch(sub_type) {
    case CardSubType::ALIEN: ss << " [Alien] "; break;
    case CardSubType::UPLIFT: ss << " [Uplift] "; break;
    case CardSubType::REBEL: ss << " [Rebel] "; break;
    case CardSubType::IMPERIUM: ss << " [Imperium] "; break;
    case CardSubType::NONE: break;
    }


    ss << " [";
    ss << ((powers & POWER_EXPLORE) ? "1" : "-");
    ss << ((powers & POWER_DEVELOP) ? "2" : "-");
    ss << ((powers & POWER_SETTLE) ? "3" : "-");
    ss << ((powers & POWER_TRADE) ? "$" : "-");
    ss << ((powers & POWER_CONSUME) ? "4" : "-");
    ss << ((powers & POWER_PRODUCE) ? "5" : "-");
    ss << "]";

    if(increase_military != 0) {
        ss << ((increase_military > 0) ? " (+" : " (");
        ss << increase_military << " mil)";
    }

    return ss.str();
}



// Six Devs
static int score_free_trade_association(const vector<Card> &tableau) {
    int score = 0;
    for(auto it = begin(tableau); it != end(tableau); ++it) {

        // Consumer Markets/Expanding Colony
        if(it->id == 354516 || it->id == 357384)
            score += 2;

        if(it->type == Card::CardType::PLANET_NOVELTY)
            score += 2;

        if(it->type == Card::CardType::PLANET_NOVELTY_WINDFALL)
            score += 1;

    }
    return score;
}

static int score_galactic_imperium(const vector<Card> &tableau) {
    int score = 0;
    for(auto it = begin(tableau); it != end(tableau); ++it) {
        if(it->military)
            score += (it->sub_type == Card::CardSubType::REBEL) ? 2 : 1;
    }
    return score;
}


static int score_alien_tech_institute(const vector<Card> &tableau) { return 0; }
static int score_galactic_federation(const vector<Card> &tableau)  { return 0; }
static int score_galactic_renaissance(const vector<Card> &tableau)  { return 0; }
static int score_galactic_survey_seti(const vector<Card> &tableau)  { return 0; }
static int score_merchant_guild(const vector<Card> &tableau)  { return 0; }
static int score_mining_league(const vector<Card> &tableau)  { return 0; }
static int score_new_economy(const vector<Card> &tableau)  { return 0; }
static int score_new_galactic_order(const vector<Card> &tableau)  { return 0; }
static int score_pan_galactic_league(const vector<Card> &tableau)  { return 0; }
static int score_trade_league(const vector<Card> &tableau)  { return 0; }
