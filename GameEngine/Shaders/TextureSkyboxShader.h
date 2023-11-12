#pragma once
#include "Shader.h"

class TextureSkyboxShader : public Shader{
public:
    TextureSkyboxShader();
    string getName() override;
};
