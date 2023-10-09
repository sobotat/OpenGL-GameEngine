#include "UtilClass.h"

#include <sstream>
#include <vector>

string UtilClass::getClassName(const type_info& info) {
    string name = info.name();
    std::istringstream iss(name);
    vector<std::string> tokens;
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens[1];
}
