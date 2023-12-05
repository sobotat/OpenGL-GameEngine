#pragma once
#include "Location.h"
#include "Transform.hpp"

class MoveOnLine : public Location {
protected:
    vec3 startLocation;
    vec3 direction;
    float progress;
public:
    MoveOnLine(vec3 direction, float progress);
    MoveOnLine(vec3 startLocation, vec3 direction, float progress);
    
    mat4 transform() override;

    void setProgress(float progress);
    float getProgress();
};
