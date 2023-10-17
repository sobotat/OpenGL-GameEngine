#include "VertexShader.h"

#include "../Utils/UtilFile.h"

VertexShader::VertexShader() {
    printf("Creating [%s] Shader ...\n", getName().c_str());
    source = UtilFile::readFile("Shaders/ShadersFiles/Vertex.vert");

    shader = glCreateShader(GL_VERTEX_SHADER);
    const char* cSource = source.c_str();
    glShaderSource(shader, 1, &cSource, NULL);
    printf("[%s] Shader Created\n", getName().c_str());
}

string VertexShader::getName() {
    return UtilClass::getClassName(typeid(this));
}
