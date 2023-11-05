#include "PointLight.h"

void PointLight::setPosition(vec3 position) {
    this->position = position;
    notifyLightChanged();
}

vec3 PointLight::getPosition() {
    return this->position;
}

void PointLight::setDimmingFactor(float factor) {
    this->dimmingFactor = factor;
    notifyLightChanged();
}

float PointLight::getDimmingFactor() {
    return this->dimmingFactor;
}
