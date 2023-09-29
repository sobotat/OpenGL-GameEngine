#include "VertexShader.h"

VertexShader::VertexShader() {
    printf("Creating Vertex Shader ...\n");
    source = "#version 330\n"
             "layout(location=0) in vec3 vp;"
             "out vec4 pos;"
             "void main () {"
             "     pos = vec4 (vp, 1.0);"
             "     gl_Position = pos;"
             "}";

    shader = glCreateShader(GL_VERTEX_SHADER);
    const char* cSource = source.c_str();
    glShaderSource(shader, 1, &cSource, NULL);
    printf("Vertex Shader Created\n");
}
