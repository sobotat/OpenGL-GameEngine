#pragma once
#include "Mesh.h"

class TextureMesh : public Mesh {
public:
    void setPoints(vector<float> meshPoints) override;
};
