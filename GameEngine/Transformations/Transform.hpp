#pragma once
#include <glm/mat4x4.hpp>

using namespace glm;
using namespace std;

class Transform {
public:
    virtual ~Transform() = default;
    virtual mat4 transform() = 0;
};