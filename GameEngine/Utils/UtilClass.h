#pragma once
#include <string>
#include <typeinfo>

using namespace std;

class UtilClass {
public:
    static string getClassName(const type_info& info);
    
    static int randomIntRange(int start, int end);
    static float randomFloatRange(float start, float end);
};
