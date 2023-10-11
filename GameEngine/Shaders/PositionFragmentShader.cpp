#include "PositionFragmentShader.h"

PositionFragmentShader::PositionFragmentShader() {
    printf("Creating [%s] Shader ...\n", getName().c_str());
    source = "#version 330\n"
             "in vec3 color;"
             "out vec4 frag_colour;"
             "void main () {"
             "  frag_colour = vec4(color, 1.0f);"
             "}";

    shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* cSource = source.c_str(); 
    glShaderSource(shader, 1, &cSource, NULL);
    printf("[%s] Shader Created\n", getName().c_str());
}

string PositionFragmentShader::getName() {
    return UtilClass::getClassName(typeid(this));
}
