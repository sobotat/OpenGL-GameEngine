#include "Light.h"

#include <iso646.h>
#include <memory>

void Light::notifyLightChanged() {
    for(LightListener* listener : listeners) {
        listener->onLightChanged(shared_from_this());
    }
}

void Light::setOn(bool on) {
    this->on = on;
    notifyLightChanged();
}

bool Light::isOn() {
    return this->on;
}

void Light::setColor(vec4 color) {
    this->color = color;
    notifyLightChanged();
}

vec4 Light::getColor() {
    return this->color * (intensity * (on ? 1 : 0));
}

void Light::setDiffuseFactor(float factor) {
    this->diffuseFactor = factor;
    notifyLightChanged();
}

float Light::getDiffuseFactor() {
    return this->diffuseFactor * (on ? 1 : 0);
}

void Light::setIntensity(float intensity) {
    this->intensity = intensity;
    notifyLightChanged();
}

float Light::getIntensity() {
    return this->intensity;
}

void Light::addOnLightChangeListener(LightListener* listener) {
    this->listeners.push_back(listener);
}
