#pragma once
#include "../Shaders/ShaderProgram.h"
#include "../Meshes/Mesh.h"
#include "../Transformations/TransformComposite.h"

class Actor {
protected:
    ShaderProgram* shaderProgram;
    Mesh* mesh;
    TransformComposite* transform = nullptr;
    
public:
    Actor(Mesh* mesh, ShaderProgram* shaderProgram);
    virtual ~Actor();

    Actor* addTransform(Transform* transform);
    
    virtual void tick();
    virtual void draw();    
};
