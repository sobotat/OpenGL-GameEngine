#include "PositionFragmentShader.h"

PositionFragmentShader::PositionFragmentShader() {
    printf("Creating [%s] Shader ...\n", getName().c_str());
    source = "#version 330\n"
             "in vec4 pos;"
             "out vec4 frag_colour;"
             "void main () {"
             "  frag_colour = vec4 (pos.x,pos.y,pos.z, 1);"
             "}";

    shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* cSource = source.c_str(); 
    glShaderSource(shader, 1, &cSource, NULL);
    printf("[%s] Shader Created\n", getName().c_str());
}

string PositionFragmentShader::getName() {
    return UtilClass::getClassName(typeid(this));
}
