#pragma once
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
using namespace std;

class Transform {
protected:
    mat4 matrix = mat4(1.0f);
public:
    virtual ~Transform() = default;
    virtual mat4 transform() = 0;
};