#include "Actor.h"

#include "../Transformations/Rotation.h"

Actor::Actor(Mesh* mesh, shared_ptr<ShaderProgram> shaderProgram, shared_ptr<Material> material) {
    this->mesh = mesh;
    this->shaderProgram = shaderProgram;
    this->transform = make_shared<TransformComposite>();

    if (material == nullptr) {
        printf("\033[1;31mMaterial Not Found\033[0m\n");
        this->material = make_shared<Material>(vec4{1, 0, 1, 1}, 1, 1);
    } else
        this->material = material;
    
}

Actor* Actor::addTransform(shared_ptr<Transform> transform) {
    this->transform->addTransform(transform);
    return this;
}

mat4 Actor::getActorMatrix() {
    return this->transform->transform();
}

mat4 Actor::getActorMatrixBefore(Transform* transform) {
    return this->transform->transformBefore(transform);
}

shared_ptr<Material> Actor::getMaterial() {
    return this->material;
}

Mesh* Actor::getMesh() {
    return mesh;
}

void Actor::tick() {
    transform->tick();
}

void Actor::draw() {    
    shaderProgram->useProgram();
    shaderProgram->setProperty(transform->transform(), "modelMatrix");

    material->applyMaterial(shaderProgram);
    
    mesh->draw();
    
    ShaderProgram::resetProgram();
}
