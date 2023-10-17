#include "TransformComposite.h"

TransformComposite::~TransformComposite() {
    for (Transform* transform : transforms) {
        delete transform;
    }
    transforms.clear();
}

mat4 TransformComposite::transform() {
    mat4 matrix = mat4(1.0f);
    for (Transform* transform : transforms) {
        matrix *= transform->transform();
    }
    return matrix;
}

TransformComposite* TransformComposite::addTransform(Transform* transform) {
    transforms.push_back(transform);
    return this;
}
