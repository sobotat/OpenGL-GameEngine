#include "FragmentShader.h"

FragmentShader::FragmentShader() {
    printf("Creating Fragment Shader ...\n");
    source = "#version 330\n"
             "out vec4 frag_colour;"
             "void main () {"
             "     frag_colour = vec4 (0.0, 1.0, 0.5, 1.0);"
             "}";

    shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* cSource = source.c_str(); 
    glShaderSource(shader, 1, &cSource, NULL);
    printf("Shader Created\n");
}
