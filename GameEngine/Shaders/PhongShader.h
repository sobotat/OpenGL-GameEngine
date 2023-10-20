#pragma once
#include "Shader.h"

class PhongShader : public Shader {
public:
    PhongShader();

    string getName() override;
};
