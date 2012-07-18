#include "misc.hh"

#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

// helper, splits a string on delim into vector
vector<string> split_line(string line, char delim) {
    vector<string> ret;
    stringstream ss(line);
    string field;
    while(getline(ss,field,delim)) {
        ret.push_back(field);
    }
    return ret;
}

// helper, trims spaces from a string
string trim(string str) {
    str.erase(begin(str), find_if(begin(str), end(str), [](char c){return c != ' ';}));
    str.erase(find_if(str.rbegin(), str.rend(), [](char c){return c != ' ';}).base(), end(str));
    return str;
}

