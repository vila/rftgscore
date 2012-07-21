#ifndef MISC_H
#define MISC_H

#include <string>
#include <vector>

std::string trim(std::string str);
std::vector<std::string> split_line(std::string line, char delim = ';');
std::vector<std::string> list_directory(const std::string& path);
std::string itos(int i);
void str_replace(std::string& str, const std::string& what, const std::string& with);


#endif /* MISC_H */
