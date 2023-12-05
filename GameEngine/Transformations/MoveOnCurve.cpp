#include "MoveOnCurve.h"

#include "Application.h"
#include "Scale.h"

MoveOnCurve::MoveOnCurve(mat4x3 firstCurve, float progress) : Location(vec3(0)) {
    this->coefficients = mat4{
        vec4{-1.0, 3.0, -3.0, 1},
        vec4{3.0, -6.0, 3.0, 0},
        vec4{-3.0, 3.0, 0, 0},
        vec4{1, 0, 0, 0}
    };
    this->curvePoints.push_back(firstCurve);
    this->progress = progress;
}

MoveOnCurve::MoveOnCurve(mat4 coefficients, mat4x3 firstCurve, float progress) : Location(vec3(0)) {
    this->coefficients = coefficients;
    this->curvePoints.push_back(firstCurve);
    this->progress = progress;
}

mat4 MoveOnCurve::transform() {    
    const int wholeProgress = static_cast<int>(progress);
    const float t = progress - static_cast<float>(wholeProgress);
    const vec4 parameters = vec4(t * t * t, t * t, t, 1.0f);
    
    if (wholeProgress < curvePoints.size())        
        moveVector = parameters * coefficients * transpose(curvePoints.at(wholeProgress));
    
    return Location::transform();
}

void MoveOnCurve::setProgress(float progress) {
    this->progress = progress;
}

float MoveOnCurve::getProgress() {
    return this->progress;
}

void MoveOnCurve::addPoint(vec3 tangent, vec3 point) {
    vec3 lastTangent = curvePoints.at(curvePoints.size() - 1)[2];
    vec3 lastPoint = curvePoints.at(curvePoints.size() - 1)[3];
    
    float distance = glm::distance(lastTangent, lastPoint);    
    vec3 direction = normalize(lastPoint - lastTangent);
    vec3 invertedTangent = lastPoint + direction * distance;
    
    curvePoints.push_back({ lastPoint, invertedTangent, tangent, point });
}
