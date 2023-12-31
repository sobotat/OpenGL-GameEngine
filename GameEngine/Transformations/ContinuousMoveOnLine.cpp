﻿#include "ContinuousMoveOnLine.h"

ContinuousMoveOnLine::ContinuousMoveOnLine(vec3 direction, float speed, bool reverse) : MoveOnLine(direction, 0) {
    this->speed = speed;
    this->reverse = reverse;
}

ContinuousMoveOnLine::ContinuousMoveOnLine(vec3 startLocation, vec3 direction, float speed, bool reverse) : MoveOnLine(startLocation, direction, 0) {    
    this->speed = speed;
    this->reverse = reverse;
}

void ContinuousMoveOnLine::tick() {
    if (reverse) {
        if (progress > 1.0f || progress < 0.0f) speed *= -1;
    } else {
        if (progress >= 1.0f || progress <= 0.0f) return;
    }
    progress += speed;
}
