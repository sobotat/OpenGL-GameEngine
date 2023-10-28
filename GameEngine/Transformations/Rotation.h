#pragma once
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#include "Transform.hpp"

class Rotation : public Transform {
protected:
    float angle;
    vec3 axis;
    
public:
    Rotation(float angle, vec3 axis);
    void tick() override;
    mat4 transform() override;
};