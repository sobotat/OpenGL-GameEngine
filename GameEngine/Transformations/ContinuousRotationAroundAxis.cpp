#include "ContinuousRotationAroundAxis.h"

#include <glm/ext/quaternion_common.hpp>

#include "ContinuousRotation.h"
#include "Location.h"
#include "Rotation.h"
#include "RotationAroundAxis.h"

ContinuousRotationAroundAxis::ContinuousRotationAroundAxis(float angle, vec3 axis, mat4 actorMatrix, shared_ptr<Actor> parentActor, float speed) {
    this->angle = radians(angle);
    this->axis = axis;
    this->speed = speed;
    this->actorAndParentDistance = vec3(parentActor->getActorMatrix()[3]) - vec3(actorMatrix[3]); 
    this->actorMatrix = actorMatrix;
    this->parentActor = parentActor;
}

void ContinuousRotationAroundAxis::tick() {
    transforms.clear();

    angle += radians(speed);
    mat4 parentMatrix = parentActor->getActorMatrix();
    vec3 location = vec3(parentMatrix[3]) - vec3(actorMatrix[3]);
    
    addTransform(make_shared<Location>(location));
    addTransform(make_shared<Rotation>(angle, axis));
    addTransform(make_shared<Location>(-actorAndParentDistance));
}

mat4 ContinuousRotationAroundAxis::transform() {
    mat4 inverse = mat4(glm::inverse(mat3(actorMatrix)));
    
    mat4 matrix = mat4(1);
    matrix *= inverse;
    matrix *= TransformComposite::transform();
    matrix *= mat4(mat3(actorMatrix));
    
    return matrix;
}
