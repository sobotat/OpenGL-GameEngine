﻿#pragma once
#include "Shader.h"

class VertexShader : public Shader {
    
public:
    VertexShader();

    string getName() override;
};
