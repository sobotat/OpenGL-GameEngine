#include "RotationAroundAxis.h"

#include "ContinuousRotation.h"
#include "Location.h"
#include "Rotation.h"
#include "Scale.h"

RotationAroundAxis::RotationAroundAxis(float angle, vec3 axis, mat4 yourMatrix, mat4 parentMatrix) {
    this->angle = radians(angle);
    this->axis = axis;
    this->parentMatrix = parentMatrix;
    
    vec3 location = vec3(parentMatrix[3]) - vec3(yourMatrix[3]);
    vec3 originalScaling = vec3(1) / vec3(length(yourMatrix[0]), length(yourMatrix[1]), length(yourMatrix[2]));
    
    addTransform(make_shared<Scale>(originalScaling));
    addTransform(make_shared<Location>(location));
    addTransform(make_shared<Rotation>(angle, axis));
    addTransform(make_shared<Location>(-location));
    addTransform(make_shared<Scale>(1.0f / originalScaling));
}
