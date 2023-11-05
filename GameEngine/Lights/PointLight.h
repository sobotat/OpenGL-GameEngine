#pragma once
#include "Light.h"

class PointLight : public Light{
protected:
    vec3 position = vec3{0, 0, 0};
    float dimmingFactor = 0.01f;
public:
    virtual void setPosition(vec3 position);
    virtual vec3 getPosition();
    virtual void setDimmingFactor(float factor);
    virtual float getDimmingFactor();
};
