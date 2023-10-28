#pragma once
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#include "TransformComposite.h"

class RotationAroundAxis : public TransformComposite {
protected:
    float angle;
    vec3 axis;
    mat4 parentMatrix;
    
public:
    RotationAroundAxis(float angle, vec3 axis, mat4 yourMatrix, mat4 parentMatrix);
};
