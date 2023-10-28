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

int UtilClass::randomIntRange(int start, int end) {
    return rand() % (end - start + 1) + start;
}

float UtilClass::randomFloatRange(float start, float end) {
    int randomInt = rand();
    return start + static_cast<float>(randomInt) / RAND_MAX * (end - start);    
}
