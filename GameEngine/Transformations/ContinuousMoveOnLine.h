#pragma once
#include "MoveOnLine.h"

class ContinuousMoveOnLine : public MoveOnLine {
    float speed;
    bool reverse;
public:
    ContinuousMoveOnLine(vec3 direction, float speed, bool reverse = true);
    ContinuousMoveOnLine(vec3 startLocation, vec3 direction, float speed, bool reverse = true);
    void tick() override;
};
