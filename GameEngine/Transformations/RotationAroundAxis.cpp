#include "RotationAroundAxis.h"

#include "ContinuousRotation.h"
#include "Location.h"
#include "Rotation.h"
#include "Scale.h"

RotationAroundAxis::RotationAroundAxis(float angle, vec3 axis, mat4 actorMatrix, mat4 parentMatrix) {
    this->angle = radians(angle);
    this->axis = axis;
    this->actorAndParentDistance = vec3(parentMatrix[3]) - vec3(actorMatrix[3]); 
    this->actorMatrix = actorMatrix;
    this->parentMatrix = parentMatrix;
    
    vec3 location = vec3(parentMatrix[3]) - vec3(actorMatrix[3]);
    
    addTransform(make_shared<Location>(location));
    addTransform(make_shared<Rotation>(angle, axis));
    addTransform(make_shared<Location>(-actorAndParentDistance));
}

mat4 RotationAroundAxis::transform() {
    mat4 inverse = mat4(glm::inverse(mat3(actorMatrix)));
    
    mat4 matrix = mat4(1);
    matrix *= inverse;
    matrix *= TransformComposite::transform();
    matrix *= mat4(mat3(actorMatrix));
    
    return matrix;
}
