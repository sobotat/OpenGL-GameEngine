#pragma once
#include "Shader.h"

class BlinnShader : public Shader {
public:
    BlinnShader();

    string getName() override;
};
