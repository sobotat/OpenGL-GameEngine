#pragma once
#include "Shader.h"

class PositionFragmentShader : public Shader {
    
public:
    PositionFragmentShader();

    string getName() override;
};
