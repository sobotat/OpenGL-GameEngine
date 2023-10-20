#pragma once

class Light;

#include "Light.h"

class LightListener {
public:
    virtual ~LightListener() = default;
    virtual void onLightChanged(Light* light) = 0;
};
