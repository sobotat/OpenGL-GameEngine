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

        printf("\nShader compilation error: %s", infoLog.data());
        return false;
    }

    return true;
}

void Shader::compile() {
    printf("Compiling Shader [%s] ...\n", getName().c_str());
    if (shader == NULL) {
        printf("Failed to compile Shader [%s] -> shader is null\n", getName().c_str());
        return;
    }
    glCompileShader(shader);

    isCompiled = checkCompile();
    if (isCompiled) {
        printf("Shader [%s] Successfully Compiled\n", getName().c_str());
    } else {
        printf("Shader [%s] Failed to Compile\n", getName().c_str());
    }    
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
