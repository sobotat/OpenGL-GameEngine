#pragma once
#include "Shader.h"

class BlinnUnlimitedShader : public Shader {
public:
    BlinnUnlimitedShader();

    string getName() override;
};
