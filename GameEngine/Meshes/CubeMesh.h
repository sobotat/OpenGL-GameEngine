#pragma once
#include "Mesh.h"

class CubeMesh : public Mesh {
public:
    CubeMesh();
    void setPoints(vector<float> meshPoints) override;
};
