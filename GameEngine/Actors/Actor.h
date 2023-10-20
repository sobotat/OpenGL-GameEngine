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
    
    vec4 color = vec4{0.15, 0.73, 0.45, 1};
    
public:
    Actor(Mesh* mesh, shared_ptr<ShaderProgram> shaderProgram);

    Actor* addTransform(shared_ptr<Transform> transform);

    void setColor(vec4 color);
    vec4 getColor();
    
    virtual void tick();
    virtual void draw();    
};
