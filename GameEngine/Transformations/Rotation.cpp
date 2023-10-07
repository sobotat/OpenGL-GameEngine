#include "Rotation.h"

Rotation::Rotation(float angle, vec3 axis) {
    this->angle = angle;
    this->axis = axis;
}

mat4 Rotation::transform() {
    return rotate(matrix, angle, axis);
}