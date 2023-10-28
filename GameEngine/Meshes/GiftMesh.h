#pragma once
#include <memory>

#include "Mesh.h"

class GiftMesh : public Mesh{
protected:
    shared_ptr<vector<float>> data;
public:
    GiftMesh();
};