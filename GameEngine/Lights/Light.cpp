#include "Light.h"

void Light::notifyLightChanged() {
    for(LightListener* listener : listeners) {
        listener->onLightChanged(this);
    }
}

Light::Light(vec3 position, vec4 color) {
    this->position = position;
    this->color = color;
}

void Light::setPosition(vec3 position) {
    this->position = position;
    
}

void Light::setColor(vec4 color) {
    this->color = color;
    
}

vec3 Light::getPosition() {
    return this->position;
}

vec4 Light::getColor() {
    return this->color;
}

void Light::addOnLightChangeListener(LightListener* listener) {
    this->listeners.push_back(listener);
}
