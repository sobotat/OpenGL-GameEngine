#pragma once
#include "PointLight.h"

class SpotLight : public PointLight {
protected:
    vec3 direction = vec3{0, 0, 1};
    float angle = 20.0f;
    float fadeStartAngle = 15.0f;
public:
    virtual void setDirection(vec3 direction);
    virtual vec3 getDirection();
    virtual void setAngle(float angle);
    virtual float getAngle();
    virtual void setFadeStartAngle(float angle);
    virtual float getFadeStartAngle();
};
