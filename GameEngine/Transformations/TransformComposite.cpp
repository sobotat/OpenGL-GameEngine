#include "TransformComposite.h"

TransformComposite::~TransformComposite() {
    transforms.clear();
}

void TransformComposite::tick() {
    for (shared_ptr<Transform>& transform : transforms) {
        transform->tick();
    }
}

mat4 TransformComposite::transform() {
    mat4 matrix = mat4(1.0f);
    for (shared_ptr<Transform>& transform : transforms) {
        matrix *= transform->transform();
    }
    return matrix;
}

mat4 TransformComposite::transformBefore(Transform* transform) {
    mat4 matrix = mat4(1.0f);
    for (shared_ptr<Transform>& t : transforms) {
        if (t.get() == transform) break;
        matrix *= t->transform();
    }
    return matrix;
}

void TransformComposite::addTransform(shared_ptr<Transform> transform) {
    transforms.push_back(transform);
}
