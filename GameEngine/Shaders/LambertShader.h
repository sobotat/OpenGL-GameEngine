#pragma once
#include "Shader.h"

class LambertShader : public Shader {
    
public:
    LambertShader();

    string getName() override;
};
