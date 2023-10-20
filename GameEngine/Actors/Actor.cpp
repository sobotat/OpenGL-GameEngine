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

void Actor::setColor(vec4 color) {
    this->color = color;
}

vec4 Actor::getColor() {
    return this->color;
}

void Actor::tick() {
}

void Actor::draw() {    
    shaderProgram->useProgram();
    shaderProgram->setPropertyMatrix(transform->transform(), "modelMatrix");
    shaderProgram->setPropertyVec4(getColor(), "meshColor");
    
    mesh->draw();
    
    ShaderProgram::resetProgram();
}
