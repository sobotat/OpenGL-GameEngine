#pragma once
#include "Shader.h"

class PhongUnlimitedShader : public Shader {
public:
    PhongUnlimitedShader();

    string getName() override;
};
