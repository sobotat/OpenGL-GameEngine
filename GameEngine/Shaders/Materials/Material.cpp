#include "Material.h"
#include <GL/glew.h>

Material::Material(vec4 color, float shininess, float specular) {
    this->color = color;
    this->shininess = shininess;
    this->specular = specular;
}

void Material::applyMaterial(shared_ptr<ShaderProgram> shaderProgram) {
    shaderProgram->setProperty(color, "meshColor");
    shaderProgram->setProperty(ambient, "meshAmbientColor");
    shaderProgram->setProperty(shininess, "shininess");
    shaderProgram->setProperty(specular, "specular");
    
    if (texture) {
        shaderProgram->setProperty(1, "hasTexture");
        texture->apply();
        shaderProgram->setProperty(0, "textureUnitID");
        shaderProgram->setProperty(texture->getTextureScale(), "textureScale");
    }
    else {
        shaderProgram->setProperty(0, "hasTexture");
    }
}

vec4 Material::getColor() const {
    return color;
}

void Material::setColor(const vec4& color) {
    this->color = color;
}

vec4 Material::getAmbient() const {
    return this->ambient;
}

void Material::setAmbient(const vec4& ambient) {
    this->ambient = ambient;
}

float Material::getShininess() const {
    return shininess;
}

void Material::setShininess(float shininess) {
    this->shininess = shininess;
}

float Material::getSpecular() const {
    return specular;
}

void Material::setSpecular(float specular) {
    this->specular = specular;
}

shared_ptr<Texture> Material::getTexture() {
    return this->texture;
}

void Material::setTexture(shared_ptr<Texture> texture) {
    this->texture = texture;
}
