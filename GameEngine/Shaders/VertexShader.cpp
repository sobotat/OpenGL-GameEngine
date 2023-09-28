#include "VertexShader.h"

VertexShader::VertexShader() {
    printf("Creating Vertex Shader ...\n");
    source = "#version 330\n"
             "layout(location=0) in vec3 vp;"
             "void main () {"
             "     gl_Position = vec4 (vp, 1.0);"
             "}";

    shader = glCreateShader(GL_VERTEX_SHADER);
    const char* cSource = source.c_str();
    glShaderSource(shader, 1, &cSource, NULL);
    printf("Shader Created\n");
}
