#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "LightListener.hpp"

class LightListener;

using namespace glm;
using namespace std;
class Light : public enable_shared_from_this<Light> {
protected:
    bool on = true;
    vec4 color = vec4{.7, .7, .7, 1};
    float intensity = 1.0f;
    float diffuseFactor = 0.5f;

    vector<LightListener*> listeners;
    void notifyLightChanged();

public:
    virtual ~Light() = default;
    virtual void setOn(bool on);
    virtual bool isOn();
    virtual void setColor(vec4 color);
    virtual vec4 getColor();
    virtual void setDiffuseFactor(float factor);
    virtual float getDiffuseFactor();
    virtual void setIntensity(float intensity);
    virtual float getIntensity();

    void addOnLightChangeListener(LightListener* listener);
};
