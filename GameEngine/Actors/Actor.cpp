#include "Actor.h"

#include "../Transformations/Rotation.h"

Actor::Actor(Mesh* mesh, shared_ptr<ShaderProgram> shaderProgram) {
    this->mesh = mesh;
    this->shaderProgram = shaderProgram;
    this->transform = make_shared<TransformComposite>();
}

Actor* Actor::addTransform(shared_ptr<Transform> transform) {
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
