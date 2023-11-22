#pragma once
#include "../Shaders/ShaderProgram.h"
#include "../Meshes/Mesh.h"
#include "../Shaders/Materials/Material.h"
#include "../Transformations/TransformComposite.h"

class Material;
class ShaderProgram;

class Actor {
protected:
    shared_ptr<ShaderProgram> shaderProgram;
    Mesh* mesh;
    shared_ptr<TransformComposite> transform = nullptr;
    shared_ptr<Material> material;
    
public:
    Actor(Mesh* mesh, shared_ptr<ShaderProgram> shaderProgram, shared_ptr<Material> material);

    Actor* addTransform(shared_ptr<Transform> transform);
    mat4 getActorMatrix();
    mat4 getActorMatrixBefore(Transform* transform);

    shared_ptr<Material> getMaterial();
    Mesh* getMesh();
    
    virtual void tick();
    virtual void draw();    
};
