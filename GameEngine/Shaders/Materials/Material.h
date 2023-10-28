#pragma once
#include <memory>

#include "../ShaderProgram.h"

class ShaderProgram;

using namespace std;
using namespace glm;
class Material {
    vec4 color;
    float shininess;
    float specular;
    
public:
    Material(vec4 color, float shininess, float specular);
    void applyMaterial(shared_ptr<ShaderProgram> shaderProgram);
};
