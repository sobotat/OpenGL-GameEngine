#pragma once
#include <vector>

#include "Meshes/Mesh.h"

using namespace std;
class Scene {
protected:
    vector<Mesh*> meshes;
    
public:
    void draw();
    void addMesh(Mesh* mesh);
    void destroyMesh(Mesh* mesh);
};
