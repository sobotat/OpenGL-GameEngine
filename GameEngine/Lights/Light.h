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

    vector<LightListener*> listeners;
    void notifyLightChanged();
    
public:
    Light(vec3 position, vec4 color = vec4{1, 1, 1, 1});

    void setPosition(vec3 position);
    void setColor(vec4 color);
    vec3 getPosition();
    vec4 getColor();

    void addOnLightChangeListener(LightListener* listener);
};
