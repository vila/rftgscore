#include "card.hh"
#include "misc.hh"

#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace rftgscore;
using namespace std;

// base 6dev
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

// tgs 6dev
static int score_galactic_genome_project(const vector<Card> &tableau);
static int score_imperium_lords(const vector<Card> &tableau);
static int score_terraforming_guild(const vector<Card> &tableau);




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
        // base
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

        // tgs
    case 451438: score = score_galactic_genome_project(tableau); break;
    case 451441: score = score_imperium_lords(tableau); break;
    case 451435: score = score_terraforming_guild(tableau); break;

    }

    return score;
}

string Card::to_string() {
    stringstream ss;

    string tmp = name;

    switch(sub_type) {
    case CardSubType::ALIEN: str_replace(tmp, "ALIEN", "[ALIEN]"); break;
    case CardSubType::UPLIFT: str_replace(tmp, "UPLIFT", "[UPLIFT]"); break;
    case CardSubType::REBEL:  str_replace(tmp, "REBEL", "[REBEL]"); break;
    case CardSubType::IMPERIUM: str_replace(tmp, "IMPERIUM", "[IMPERIUM]"); break;
    case CardSubType::TERRAFORMING: str_replace(tmp, "TERRAFORMING", "[TERRAFORMING]"); break;
    case CardSubType::NONE: break;
    }

    // name and cost/value
    ss << id << ": " << left << setw(35) << tmp;
    ss << " (" << cost << "/" << value << ") ";

    // Powers
    ss << "[";
    ss << ((powers & POWER_EXPLORE) ? "1" : "-");
    ss << ((powers & POWER_DEVELOP) ? "2" : "-");
    ss << ((powers & POWER_SETTLE) ? "3" : "-");
    ss << ((powers & POWER_TRADE) ? "$" : "-");
    ss << ((powers & POWER_CONSUME) ? "4" : "-");
    ss << ((powers & POWER_PRODUCE) ? "5" : "-");
    ss << "] ";

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

    if(increase_military != 0) {
        ss << ((increase_military > 0) ? " (+" : " (");
        ss << increase_military << " mil.)";
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


static int score_alien_tech_institute(const vector<Card> &tableau) {
    int score = 0;
    for(auto it = begin(tableau); it != end(tableau); ++it) {
        if(it->type == Card::CardType::PLANET_ALIEN)
            score += 3;
        else if(it->type == Card::CardType::PLANET_ALIEN_WINDFALL)
            score += 2;
        else if(it->sub_type == Card::CardSubType::ALIEN)
            score += 2;
    }
    return score;
}

static int score_galactic_federation(const vector<Card> &tableau)  {
    int score = 0;
    for(auto it = begin(tableau); it != end(tableau); ++it) {
        if(it->type == Card::CardType::DEVELOPMENT)
            score += (it->cost == 6) ? 2 : 1;
    }
    return score;
}

static int score_galactic_renaissance(const vector<Card> &tableau)  {
    int score = 0;
    // TODO add warning for the vp chip bonus not included in score
    for(auto it = begin(tableau); it != end(tableau); ++it) {
        // Research Lab / Artist Colony / Galactic Trendsetters
        if(it->id == 340449 || it->id == 356855 || it->id == 341379)
            score += (it->cost == 6) ? 2 : 1;
    }
    return score;
}

static int score_galactic_survey_seti(const vector<Card> &tableau)  {
    int score = 0;
    for(auto it = begin(tableau); it != end(tableau); ++it) {
        if(it->powers & Card::POWER_EXPLORE)
            score += (it->type == Card::CardType::DEVELOPMENT) ? 1 : 2;
        else if(it->type != Card::CardType::DEVELOPMENT)
            score += 1; // other world
    }
    return score;
}

static int score_merchant_guild(const vector<Card> &tableau)  {
    int score = 0;
    for(auto it = begin(tableau); it != end(tableau); ++it) {
        if(it->type == Card::CardType::PLANET_NOVELTY ||
           it->type == Card::CardType::PLANET_RARE ||
           it->type == Card::CardType::PLANET_GENE ||
           it->type == Card::CardType::PLANET_ALIEN)
            score += 2;
    }
    return score;
}

static int score_mining_league(const vector<Card> &tableau)  {
    int score = 0;
    for(auto it = begin(tableau); it != end(tableau); ++it) {
        // Mining Robots / Mining Conglomerate
        if(it->id == 354961 || it->id == 340490)
            score += 2;
        else if(it->type == Card::CardType::PLANET_RARE_WINDFALL)
            score += 1;
        else if(it->type == Card::CardType::PLANET_RARE)
            score += 2;
    }
    return score;
}

static int score_new_economy(const vector<Card> &tableau)  {
    int score = 0;
    for(auto it = begin(tableau); it != end(tableau); ++it) {
        if(it->powers & Card::POWER_CONSUME)
            score += (it->type == Card::CardType::DEVELOPMENT) ? 2 : 1;
    }
    return score;
}

static int score_new_galactic_order(const vector<Card> &tableau)  {
    int score = 0;
    for(auto it = begin(tableau); it != end(tableau); ++it) {
        score += it->increase_military;
    }
    return score;
}

static int score_pan_galactic_league(const vector<Card> &tableau)  {
    int score = 0;
    for(auto it = begin(tableau); it != end(tableau); ++it) {
        // Contact Specialist
        if(it->id == 340758)
            score += 3;
        else if(it->type == Card::CardType::PLANET_GENE ||
                it->type == Card::CardType::PLANET_GENE_WINDFALL)
            score += 2;
        else if(it->type != Card::CardType::DEVELOPMENT && it->military)
            score += 1;
    }
    return score;
}

static int score_trade_league(const vector<Card> &tableau)  {
    int score = 0;
    for(auto it = begin(tableau); it != end(tableau); ++it) {
        if(it->powers & Card::POWER_TRADE)
            score += (it->type == Card::CardType::DEVELOPMENT) ? 2 : 1;
    }
    return score;
}

// tgs 6devs

static int score_galactic_genome_project(const vector<Card> &tableau) {
    int score = 0;
    for(auto it = begin(tableau); it != end(tableau); ++it) {
        // Genetics Lab
        if(it->id == 340760)
            score += 3;

        if(it->type == Card::CardType::PLANET_GENE ||
           it->type == Card::CardType::PLANET_GENE_WINDFALL)
            score += 2;
    }
    return score;
}
static int score_imperium_lords(const vector<Card> &tableau) {
    int score = 0;
    for(auto it = begin(tableau); it != end(tableau); ++it) {
        if(it->sub_type == Card::CardSubType::IMPERIUM)
            score += 2;
        else if(it->type != Card::CardType::DEVELOPMENT && it->military)
            score += 1;
    }
    return score;    
}

static int score_terraforming_guild(const vector<Card> &tableau) {
    int score = 0;
    for(auto it = begin(tableau); it != end(tableau); ++it) {
        if(it->type == Card::CardType::PLANET_NOVELTY_WINDFALL ||
           it->type == Card::CardType::PLANET_RARE_WINDFALL ||
           it->type == Card::CardType::PLANET_GENE_WINDFALL ||
           it->type == Card::CardType::PLANET_ALIEN_WINDFALL)
            score += 2;
        else if(it->sub_type == Card::CardSubType::TERRAFORMING)
            score += 2;
    }
    return score;    
}
