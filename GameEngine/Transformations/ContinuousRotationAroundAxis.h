#pragma once
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#include "TransformComposite.h"
#include "../Actors/Actor.h"

class ContinuousRotationAroundAxis : public TransformComposite {
protected:
    float angle, speed;
    vec3 axis;
    mat4 actorMatrix;
    shared_ptr<Actor> parentActor;
    vec3 actorAndParentDistance;

public:
    ContinuousRotationAroundAxis(float angle, vec3 axis, mat4 actorMatrix, shared_ptr<Actor> parentActor, float speed = .5f);
    void tick() override;
    mat4 transform() override;
};
