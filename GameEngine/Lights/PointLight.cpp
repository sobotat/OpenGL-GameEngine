#include "PointLight.h"

void PointLight::setPosition(vec3 position) {
    this->position = position;
    notifyLightChanged();
}

vec3 PointLight::getPosition() {
    return this->position;
}

void PointLight::setDimmingFactorLinear(float factor) {
    this->dimmingFactorLinear = factor;
    notifyLightChanged();
}

float PointLight::getDimmingFactorLinear() {
    return this->dimmingFactorLinear;
}

void PointLight::setDimmingFactorQuadratic(float factor) {
    this->dimmingFactorQuadratic = factor;
    notifyLightChanged();
}

float PointLight::getDimmingFactorQuadratic() {
    return this->dimmingFactorQuadratic;
}
