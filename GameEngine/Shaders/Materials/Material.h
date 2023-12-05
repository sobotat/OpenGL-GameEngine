#pragma once
#include <memory>

#include "../ShaderProgram.h"
#include "Texture/Texture.h"

class ShaderProgram;

using namespace std;
using namespace glm;
class Material {
    vec4 color;
    vec4 ambient = vec4(.02f, .02f, .02f, 1);
    float shininess;
    float specular;
    shared_ptr<Texture> texture = nullptr;
    
public:
    Material(vec4 color, float shininess, float specular);
    void applyMaterial(shared_ptr<ShaderProgram> shaderProgram);

    vec4 getColor() const;
    void setColor(const vec4& color);
    vec4 getAmbient() const;
    void setAmbient(const vec4& ambient);
    float getShininess() const;
    void setShininess(float shininess);
    float getSpecular() const;
    void setSpecular(float specular);
    shared_ptr<Texture> getTexture();
    void setTexture(shared_ptr<Texture> texture);
};
