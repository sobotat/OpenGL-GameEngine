#include "Light.h"

#include <memory>

void Light::notifyLightChanged() {
    for(LightListener* listener : listeners) {
        listener->onLightChanged(shared_ptr<Light>(this));
    }
}

Light::Light(vec3 position, vec4 color, float dimmingFactor) {
    this->position = position;
    this->color = color;
    this->dimmingFactor = dimmingFactor;
}

void Light::setPosition(vec3 position) {
    this->position = position;
    
}

void Light::setColor(vec4 color) {
    this->color = color;
    
}

void Light::setDimmingFactor(float factor) {
    this->dimmingFactor = factor;
}

vec3 Light::getPosition() {
    return this->position;
}

vec4 Light::getColor() {
    return this->color;
}

float Light::getDimmingFactor() {
    return this->dimmingFactor;
}

void Light::addOnLightChangeListener(LightListener* listener) {
    this->listeners.push_back(listener);
}
