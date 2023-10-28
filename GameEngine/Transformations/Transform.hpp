#pragma once
#include <glm/mat4x4.hpp>

using namespace glm;
using namespace std;

class Transform {
public:
    virtual ~Transform() = default;
    virtual void tick() = 0;
    virtual mat4 transform() = 0;
};