#include "Shader.h"

void Shader::compile() {
    printf("Compiling Shader [%s] ...\n", getName().c_str());
    if (shader == NULL) {
        printf("Failed to compile Shader [%s] -> shader is null\n", getName().c_str());
        return;
    }
    glCompileShader(shader);
    isCompiled = true;
    printf("Shader [%s] Compiled\n", getName().c_str());
}

void Shader::attach(GLuint shaderProgram) {
    printf("Attaching Shader ...\n");
    if(!isCompiled) {
        printf("Failed to attach Shader [%s] -> Shader was not compiled", getName().c_str());
        return;
    }
    if (shader == NULL) {
        printf("Failed to attach Shader [%s] -> shader is null\n", getName().c_str());
        return;
    }
    glAttachShader(shaderProgram, shader);
    printf("Shader [%s] Attached\n", getName().c_str());
}

string Shader::getName() {
    return UtilClass::getClassName(typeid(this));
}
