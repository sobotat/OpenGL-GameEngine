#pragma once

class Light;

#include "Light.h"
#include <memory>

using namespace std;
class LightListener {
public:
    virtual ~LightListener() = default;
    virtual void onLightChanged(shared_ptr<Light> light) = 0;
};
