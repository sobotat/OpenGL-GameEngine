#include "VertexShader.h"

VertexShader::VertexShader() {
    printf("Creating [%s] Shader ...\n", getName().c_str());
    source = "#version 330\n"
             "layout(location=0) in vec3 vp;\n"
             "layout(location=1) in vec3 vp_color;\n"
             "uniform mat4 modelMatrix;\n"
             "out vec4 pos;\n"
             "out vec3 color;\n"
             "void main () {"
             "     pos = modelMatrix * vec4 (vp, 1.0);"
             "     gl_Position = pos;"
             "     color = vp_color;"
             "}";

    shader = glCreateShader(GL_VERTEX_SHADER);
    const char* cSource = source.c_str();
    glShaderSource(shader, 1, &cSource, NULL);
    printf("[%s] Shader Created\n", getName().c_str());
}

string VertexShader::getName() {
    return UtilClass::getClassName(typeid(this));
}
