#pragma once
#include "Shader.h"

class TextureShader : public Shader{
public:
    TextureShader();
    string getName() override;
};
