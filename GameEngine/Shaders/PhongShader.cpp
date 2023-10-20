#include "PhongShader.h"

#include "../Utils/UtilFile.h"

PhongShader::PhongShader() {
    printf("Creating [%s] Shader ...\n", getName().c_str());
    source = UtilFile::readFile("Shaders/ShadersFiles/Phong.frag");

    shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* cSource = source.c_str(); 
    glShaderSource(shader, 1, &cSource, NULL);
    printf("\033[0;32m[%s] Shader Created\033[0m\n", getName().c_str());
}

string PhongShader::getName() {
    return UtilClass::getClassName(typeid(this));
}