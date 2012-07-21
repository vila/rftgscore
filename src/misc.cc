#include "misc.hh"

#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

#include <dirent.h>

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

vector<string> list_directory(const string& path) {
    vector<string> ret;
    DIR *dir = opendir(path.c_str());
    
    dirent *file;
    while((file = readdir(dir)) != NULL) {
        string filename(file->d_name);

        if(filename != "." && filename != "..")
            ret.push_back(filename);
    }
    return ret;
}

// helper, int to string
string itos(int i) {
    stringstream ss;
    ss << i;
    return ss.str();
}

// helper, replace string 
void str_replace(std::string& str, const std::string& what, const std::string& with) {
    size_t pos = str.find(what);
    if(pos != string::npos)
        str.replace(pos, what.size(), with);
}
