#pragma once
#include "Location.h"
#include "Transform.hpp"

class MoveOnLine : public Location {
protected:
    vec3 startLocation;
    vec3 endLocation;
    float progress;
public:
    MoveOnLine(vec3 endLocation, float progress);
    MoveOnLine(vec3 startLocation, vec3 endLocation, float progress);
    
    mat4 transform() override;

    void setProgress(float progress);
    float getProgress();
};
