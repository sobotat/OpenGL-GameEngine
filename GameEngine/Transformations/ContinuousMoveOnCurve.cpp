#include "ContinuousMoveOnCurve.h"


ContinuousMoveOnCurve::ContinuousMoveOnCurve(mat4 coefficients, mat4x3 endLocation, float speed, bool reverse) : MoveOnCurve(coefficients, endLocation, 0) {
    this->speed = speed;
    this->reverse = reverse;
}

void ContinuousMoveOnCurve::tick() {
    if (reverse) {
        if (progress > 1.0f || progress < 0.0f) speed *= -1;
    } else {
        if (progress >= 1.0f || progress <= 0.0f) return;
    }
    progress += speed;
}
