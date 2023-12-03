#include "MoveOnCurve.h"

MoveOnCurve::MoveOnCurve(mat4 coefficients, mat4x3 endLocation, float progress) : Location(vec3(0)) {
    this->coefficients = coefficients;
    this->endLocation = endLocation;
    this->progress = progress;
}

mat4 MoveOnCurve::transform() {    
    vec4 parameters = vec4(progress * progress * progress, progress * progress, progress, 1.0f);
    moveVector = parameters * coefficients * transpose(endLocation); 
    return Location::transform();
}

void MoveOnCurve::setProgress(float progress) {
    this->progress = progress;
}

float MoveOnCurve::getProgress() {
    return this->progress;
}
