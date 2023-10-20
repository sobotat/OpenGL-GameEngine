#pragma once
#include "../Shaders/ShaderProgram.h"
#include "../Meshes/Mesh.h"
#include "../Transformations/TransformComposite.h"

class ShaderProgram;

class Actor {
protected:
    shared_ptr<ShaderProgram> shaderProgram;
    Mesh* mesh;
    shared_ptr<TransformComposite> transform = nullptr;
    
public:
    Actor(Mesh* mesh, shared_ptr<ShaderProgram> shaderProgram);

    Actor* addTransform(shared_ptr<Transform> transform);
    
    virtual void tick();
    virtual void draw();    
};
