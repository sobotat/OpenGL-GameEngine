#pragma once
#include <string>
#include <typeinfo>

using namespace std;

class UtilClass {
public:
    static string getClassName(const type_info& info);
};
