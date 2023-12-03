#pragma once
#include "MoveOnCurve.h"

class ContinuousMoveOnCurve : public MoveOnCurve {
protected:
    float speed;
    bool reverse;
public:
    ContinuousMoveOnCurve(mat4 coefficients, mat4x3 endLocation, float speed, bool reverse = true);
    void tick() override;
};
