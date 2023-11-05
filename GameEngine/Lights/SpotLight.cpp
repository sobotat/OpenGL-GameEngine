#include "SpotLight.h"

void SpotLight::setDirection(vec3 direction) {
    this->direction = direction;
    notifyLightChanged();
}

vec3 SpotLight::getDirection() {
    return this->direction;
}

void SpotLight::setAngle(float angle) {
    this->angle = angle;
    notifyLightChanged();
}

float SpotLight::getAngle() {
    return this->angle;
}

void SpotLight::setFadeStartAngle(float angle) {
    this->fadeStartAngle = angle;
}

float SpotLight::getFadeStartAngle() {
    return this->fadeStartAngle;
}
