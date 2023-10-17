#include "TransformComposite.h"

TransformComposite::~TransformComposite() {
    transforms.clear();
}

mat4 TransformComposite::transform() {
    mat4 matrix = mat4(1.0f);
    for (shared_ptr<Transform>& transform : transforms) {
        matrix *= transform->transform();
    }
    return matrix;
}

shared_ptr<TransformComposite> TransformComposite::addTransform(shared_ptr<Transform> transform) {
    transforms.push_back(transform);
    return shared_from_this();
}
