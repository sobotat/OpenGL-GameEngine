#pragma once
#include "Light.h"

class PointLight : public Light{
protected:
    vec3 position = vec3{0, 0, 0};
    float dimmingFactorLinear = 0.01f;
    float dimmingFactorQuadratic = 0.01f;
public:
    virtual void setPosition(vec3 position);
    virtual vec3 getPosition();
    virtual void setDimmingFactorLinear(float factor);
    virtual float getDimmingFactorLinear();
    virtual void setDimmingFactorQuadratic(float factor);
    virtual float getDimmingFactorQuadratic();
};
