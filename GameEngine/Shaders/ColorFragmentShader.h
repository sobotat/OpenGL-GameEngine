#pragma once
#include "Shader.h"

class ColorFragmentShader : public Shader {
public:
    ColorFragmentShader();

    string getName() override;
};
