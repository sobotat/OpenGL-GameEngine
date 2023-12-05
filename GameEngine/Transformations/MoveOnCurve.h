#pragma once
#include "Location.h"

class MoveOnCurve : public Location {
protected:
    mat4 coefficients;
    vector<mat4x3> curvePoints;
    float progress;
    
public:
    MoveOnCurve(mat4x3 firstCurve, float progress);
    MoveOnCurve(mat4 coefficients, mat4x3 firstCurve, float progress);

    mat4 transform() override;

    void setProgress(float progress);
    float getProgress();

    void addPoint(vec3 tangent, vec3 point);
};
