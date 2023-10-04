#pragma once
#include "../Shaders/ShaderProgram.h"
#include "../Meshes/Mesh.h"

class Actor {
protected:
    ShaderProgram* shaderProgram = nullptr;
    Mesh* mesh;
    
public:
    Actor(Mesh* mesh, ShaderProgram* shaderProgram);
    virtual void tick();
    virtual void draw();    
};
