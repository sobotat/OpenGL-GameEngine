#include "ContinuousMoveOnCurve.h"


ContinuousMoveOnCurve::ContinuousMoveOnCurve(mat4 coefficients, mat4x3 firstPoints, float speed, bool reverse) : MoveOnCurve(coefficients, firstPoints, 0) {
    this->speed = speed;
    this->reverse = reverse;
}

void ContinuousMoveOnCurve::tick() {    
    const int max = static_cast<int>(curvePoints.size());
    if (reverse) {
        if (progress + speed > static_cast<float>(max) || progress + speed < 0.0f) speed *= -1;
    } else {
        if (progress + speed > static_cast<float>(max) || progress + speed < 0.0f) return;
    }
    progress += speed;
}
