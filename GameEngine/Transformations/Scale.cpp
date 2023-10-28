#include "Scale.h"

Scale::Scale(vec3 scaleVector) {
    this->scaleVector= scaleVector;
}

void Scale::tick() {
}

mat4 Scale::transform() {
    return scale(mat4(1.0f), scaleVector);
}
