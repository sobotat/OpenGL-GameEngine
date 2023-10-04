#include "Actor.h"

Actor::Actor(Mesh* mesh, ShaderProgram* shaderProgram) {
    this->mesh = mesh;
    this->shaderProgram = shaderProgram;
}

void Actor::tick() {}

void Actor::draw() {
    shaderProgram->useProgram();
    mesh->draw();
}
