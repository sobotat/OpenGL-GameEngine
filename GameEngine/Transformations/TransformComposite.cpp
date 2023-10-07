#include "TransformComposite.h"

TransformComposite::~TransformComposite() {
    for (Transform* transform : transforms) {
        delete transform;
    }
    transforms.clear();
}

mat4 TransformComposite::transform() {
    for (Transform* transform : transforms) {
        matrix *= transform->transform();
        delete transform;
    }
    transforms.clear();
    return matrix;
}

TransformComposite* TransformComposite::addTransform(Transform* transform) {
    transforms.push_back(transform);
    return this;
}
