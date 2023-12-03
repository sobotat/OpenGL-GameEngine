#include "MoveOnLine.h"

#include <string>
#include <glm/ext/matrix_transform.hpp>

MoveOnLine::MoveOnLine(vec3 endLocation, float progress) : Location(vec3(0)) {
    this->startLocation = vec3(0);
    this->endLocation = endLocation;
    this->progress = progress;    
}

MoveOnLine::MoveOnLine(vec3 startLocation, vec3 endLocation, float progress) : Location(startLocation) {
    this->startLocation = startLocation;
    this->endLocation = endLocation;
    this->progress = progress;    
}

mat4 MoveOnLine::transform() {
    moveVector = {(1 - progress) * startLocation[0] + progress * endLocation[0], (1 - progress) * startLocation[1] + progress * endLocation[1], (1 - progress) * startLocation[2] + progress * endLocation[2]};
    return Location::transform();
}

void MoveOnLine::setProgress(float progress) {
    this->progress = progress;
}

float MoveOnLine::getProgress() {
    return this->progress;
}
