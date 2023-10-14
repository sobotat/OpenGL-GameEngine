#include "ColorFragmentShader.h"

ColorFragmentShader::ColorFragmentShader() {
    printf("Creating [%s] Shader ...\n", getName().c_str());
    source = "#version 330\n"
             "in vec4 worldPosition;"
             "out vec4 frag_colour;"
             "void main () {"
             "     frag_colour = vec4 (0.431, 0.584, 0.776, 1);"
             "}";

    shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* cSource = source.c_str(); 
    glShaderSource(shader, 1, &cSource, NULL);
    printf("[%s] Shader Created\n", getName().c_str());
}

string ColorFragmentShader::getName() {
    return UtilClass::getClassName(typeid(this));
}
