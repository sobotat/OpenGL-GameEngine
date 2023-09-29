#include "PositionFragmentShader.h"

PositionFragmentShader::PositionFragmentShader() {
    printf("Creating Position Fragment Shader ...\n");
    source = "#version 330\n"
             "in vec4 pos;"
             "out vec4 frag_colour;"
             "void main () {"
             "     frag_colour = vec4 (0.3 - pos.x,0.3 - pos.y,0.3 - pos.z, 1);"
             "}";

    shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* cSource = source.c_str(); 
    glShaderSource(shader, 1, &cSource, NULL);
    printf("Position Fragment Shader Created\n");
}
