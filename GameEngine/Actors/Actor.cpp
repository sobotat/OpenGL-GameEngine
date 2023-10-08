#include "Actor.h"

#include "../Transformations/Rotation.h"

Actor::Actor(Mesh* mesh, ShaderProgram* shaderProgram) {
    this->mesh = mesh;
    this->shaderProgram = shaderProgram;
    this->transform = new TransformComposite();
}

Actor::~Actor() {
    delete transform;
}

Actor* Actor::addTransform(Transform* transform) {
    this->transform->addTransform(transform);
    return this;
}

void Actor::tick() {
}

void Actor::draw() {    
    shaderProgram->useProgram();
    shaderProgram->setPropertyMatrix(transform->transform(), "modelMatrix");
    
    mesh->draw();
    
    ShaderProgram::resetProgram();
}
