#include "PositionFragmentShader.h"

#include "../Utils/UtilFile.h"

PositionFragmentShader::PositionFragmentShader() {
    printf("Creating [%s] Shader ...\n", getName().c_str());
    source = UtilFile::readFile("Shaders/ShadersFiles/Position.frag");

    shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* cSource = source.c_str(); 
    glShaderSource(shader, 1, &cSource, NULL);
    printf("\033[0;32m[%s] Shader Created\033[0m\n", getName().c_str());
}

string PositionFragmentShader::getName() {
    return UtilClass::getClassName(typeid(this));
}
