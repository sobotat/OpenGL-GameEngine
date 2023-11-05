#include "DirectionalLight.h"

void DirectionalLight::setDirection(vec3 direction) {
    this->direction = direction;
    notifyLightChanged();
}

vec3 DirectionalLight::getDirection() {
    return this->direction;
}
