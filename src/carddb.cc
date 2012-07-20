#include "carddb.hh"
#include "misc.hh"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace rftgscore;
using namespace std;

Card CardDatabase::find_by_name(string name) {
    transform(begin(name), end(name), begin(name), ::toupper);

    auto it = find_if(begin(cards), end(cards),
                      [&](Card c) { return c.name == name; });

    if(it == end(cards))
        throw CardNotFoundException(name);
    return *it;
}

Card CardDatabase::find_by_id(int id) {
    auto it = find_if(begin(cards), end(cards),
                      [&](Card c) { return c.id == id; });

    if(it == end(cards))
        throw CardNotFoundException("find_by_id");
    return *it;
}



int CardDatabase::load_cards(const string& filename) {
    ifstream in(filename, ifstream::in);

    if(!in.good())
        return -1;

    
    string line;

    while(!in.eof()) {
        getline(in, line);
        if(line.size() == 0 || line[0] == '#')
            continue;

        Card card;

        vector<string> fields = split_line(line);        

        // trim spaces
        transform(begin(fields), end(fields), begin(fields), trim);

        if(fields.size() != 9) {
            // TODO error handling
            std::cerr << "Corrupt database!\n";
            return -1;
        }
        
        card.id = std::stoi(fields[0]);
        card.type = static_cast<Card::CardType>(std::stoi(fields[1]));
        card.sub_type =  static_cast<Card::CardSubType>(std::stoi(fields[2]));
        card.military = std::stoi(fields[3]) != 0;
        card.cost = std::stoi(fields[4]);
        card.value = std::stoi(fields[5]);
        card.powers = std::stoi(fields[6]);
        card.increase_military = std::stoi(fields[7]);
        card.name = fields[8];


        cards.push_back(card);
    }

    return cards.size();
}
