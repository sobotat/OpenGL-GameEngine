#include "Location.h"

Location::Location(vec3 moveVector) {
    this->moveVector = moveVector;
}

mat4 Location::transform() {
    return translate(mat4(1.0f), moveVector);
}
