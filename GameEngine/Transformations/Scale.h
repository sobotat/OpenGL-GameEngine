#pragma once
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#include "Transform.hpp"

class Scale : public Transform {
protected:
    vec3 scaleVector;
    
public:
    Scale(vec3 scaleVector);
    void tick() override;
    mat4 transform() override;
};