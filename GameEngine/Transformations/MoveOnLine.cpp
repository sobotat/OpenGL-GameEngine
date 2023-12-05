#include "MoveOnLine.h"

#include <string>
#include <glm/ext/matrix_transform.hpp>

MoveOnLine::MoveOnLine(vec3 direction, float progress) : Location(vec3(0)) {
    this->startLocation = vec3(0);
    this->direction = direction;
    this->progress = progress;    
}

MoveOnLine::MoveOnLine(vec3 startLocation, vec3 direction, float progress) : Location(vec3(0)) {
    this->startLocation = startLocation;
    this->direction = direction;
    this->progress = progress;    
}

mat4 MoveOnLine::transform() {
    moveVector = startLocation + direction * progress;
    return Location::transform();
}

void MoveOnLine::setProgress(float progress) {
    this->progress = progress;
}

float MoveOnLine::getProgress() {
    return this->progress;
}
