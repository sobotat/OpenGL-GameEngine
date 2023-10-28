#pragma once
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#include "Transform.hpp"

class ContinuousRotation : public Transform {
protected:
    float angle;
    float speed;
    vec3 axis;
    
public:
    ContinuousRotation(float angle, vec3 axis, float speed = .5f);
    void tick() override;
    mat4 transform() override;
};