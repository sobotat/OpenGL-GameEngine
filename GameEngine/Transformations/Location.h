#pragma once
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#include "Transform.hpp"

class Location : public Transform {
protected:
    vec3 moveVector;
    
public:
    Location(vec3 moveVector);
    mat4 transform() override;
};
