#include "ContinuousRotation.h"

ContinuousRotation::ContinuousRotation(float angle, vec3 axis, float speed) {
    this->angle = radians(angle);
    this->axis = axis;
    this->speed = speed;
}

void ContinuousRotation::tick() {
    this->angle += radians(speed);
}

mat4 ContinuousRotation::transform() {
    return rotate(mat4(1.0f), angle, axis);
}
