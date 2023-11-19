#pragma once
#include "vector"
#include "string"
#include <GL/glew.h>

#include "Actors/Actor.h"
#include "Texture.h"

using namespace std;
class CubeMapTexture : public Texture {
public:
    CubeMapTexture(string path, string extension);
    void apply() override;
};
