#include "ColorFragmentShader.h"

ColorFragmentShader::ColorFragmentShader() {
    printf("Creating Color Fragment Shader ...\n");
    source = "#version 330\n"
             "out vec4 frag_colour;"
             "void main () {"
             "     frag_colour = vec4 (0, 0.8, 0.3, 1);"
             "}";

    shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* cSource = source.c_str(); 
    glShaderSource(shader, 1, &cSource, NULL);
    printf("Color Fragment Shader Created\n");
}
