#include "Shader.h"

#include <vector>

bool Shader::checkCompile() {
    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        vector<GLchar> infoLog(infoLogLength);
        glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog.data());

        printf("\n%s", infoLog.data());
        return false;
    }

    return true;
}

void Shader::compile() {
    printf("Compiling Shader [%s] ...\n", getName().c_str());
    if (shader == NULL) {
        printf("\033[1;31mFailed to compile Shader [%s] -> shader is null\033[0m\n", getName().c_str());
        return;
    }
    if (source.empty()) {
        printf("\033[1;31mFailed to compile Shader [%s] -> source is empty\033[0m\n", getName().c_str());
        return;
    }
    glCompileShader(shader);

    isCompiled = checkCompile();
    if (isCompiled) {
        printf("\033[1;32mShader [%s] Successfully Compiled\033[0m\n", getName().c_str());
    } else {
        printf("\033[1;31mShader [%s] Failed to Compile\033[0m\n", getName().c_str());
        exit(2);
    }    
}

void Shader::attach(GLuint shaderProgram) {
    printf("Attaching Shader ...\n");
    if(!isCompiled) {
        printf("\033[1;33mFailed to attach Shader [%s] -> Shader was not compiled\033[0m\n", getName().c_str());
        return;
    }
    if (shader == NULL) {
        printf("\033[1;33mFailed to attach Shader [%s] -> shader is null\033[0m\n", getName().c_str());
        return;
    }
    glAttachShader(shaderProgram, shader);
    printf("\033[1;32mShader [%s] Attached\033[0m\n", getName().c_str());
}

string Shader::getName() {
    return UtilClass::getClassName(typeid(this));
}
