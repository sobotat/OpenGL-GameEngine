#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "LightListener.hpp"

class LightListener;

using namespace glm;
using namespace std;
class Light {
    vec3 position;
    vec4 color;
    float dimmingFactor;
    float diffuseFactor;

    vector<LightListener*> listeners;
    void notifyLightChanged();
    
public:
    Light(vec3 position, vec4 color = vec4{.7, .7, .7, 1}, float dimmingFactor = 0.01f, float diffuseFactor = 0.5f);

    void setPosition(vec3 position);
    void setColor(vec4 color);
    void setDimmingFactor(float factor);
    vec3 getPosition();
    vec4 getColor();
    float getDimmingFactor();
    float getDiffuseFactor();

    void addOnLightChangeListener(LightListener* listener);
};
