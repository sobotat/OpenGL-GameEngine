#pragma once
#include "Light.h"

class DirectionalLight : public Light {
protected:
    vec3 direction = vec3{0, 0, 1};
public:
    virtual void setDirection(vec3 direction);
    virtual vec3 getDirection();
};
