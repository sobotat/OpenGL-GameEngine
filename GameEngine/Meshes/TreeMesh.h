#pragma once
#include "Mesh.h"
#include <memory>

class TreeMesh : public Mesh{
protected:
    shared_ptr<vector<float>> treeData;
public:
    TreeMesh();
};