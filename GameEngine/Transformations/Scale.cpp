#include "Scale.h"

Scale::Scale(vec3 scaleVector) {
    this->scaleVector= scaleVector;
}

mat4 Scale::transform() {
    return scale(mat4(1.0f), scaleVector);
}