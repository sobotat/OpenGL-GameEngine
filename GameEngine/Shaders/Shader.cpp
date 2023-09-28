#include "Shader.h"

void Shader::compile() {
    printf("Compiling Shader ...\n");
    if (shader == NULL) {
        printf("Failed to compile Shader -> shader is null\n");
        return;
    }
    glCompileShader(shader);
    isCompiled = true;
    printf("Shader Compiled\n");
}

void Shader::attach(GLuint shaderProgram) {
    printf("Attaching Shader ...\n");
    if(!isCompiled) {
        printf("Failed to attach Shader -> Shader was not compiled");
        return;
    }
    if (shader == NULL) {
        printf("Failed to attach Shader -> shader is null\n");
        return;
    }
    glAttachShader(shaderProgram, shader);
    printf("Shader Attached\n");
}
