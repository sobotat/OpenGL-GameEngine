#pragma once
#include "Location.h"

class MoveOnCurve : public Location {
protected:
    mat4 coefficients;
    mat4x3 endLocation;
    float progress;
public:
    MoveOnCurve(mat4 coefficients, mat4x3 endLocation, float progress);

    mat4 transform() override;

    void setProgress(float progress);
    float getProgress();
};
