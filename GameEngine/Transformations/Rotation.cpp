#include "Rotation.h"

Rotation::Rotation(float angle, vec3 axis) {
    this->angle = radians(angle);
    this->axis = axis;
}

void Rotation::tick() {
}

mat4 Rotation::transform() {
    return rotate(mat4(1.0f), angle, axis);
}
