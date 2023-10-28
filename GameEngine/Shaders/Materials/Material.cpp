#include "Material.h"

Material::Material(vec4 color, float shininess, float specular) {
    this->color = color;
    this->shininess = shininess;
    this->specular = specular;
}

void Material::applyMaterial(shared_ptr<ShaderProgram> shaderProgram) {    
    shaderProgram->setProperty(color, "meshColor");
    shaderProgram->setProperty(shininess, "shininess");
    shaderProgram->setProperty(specular, "specular");
}
