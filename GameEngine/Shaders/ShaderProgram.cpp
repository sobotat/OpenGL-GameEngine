#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(vector<Shader*> shaders) {
    this->shaders = move(shaders);
    
    printf("Setting Shader Program ...\n");
    program = glCreateProgram();
    for (Shader* shader : this->shaders) {
        shader->attach(program);
    }
    glLinkProgram(program);

    printf("Checking Shaders ...\n");
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
        exit(EXIT_FAILURE);
    }
    printf("Shaders Check\n");
    printf("Shader Program Set\n");
}

void ShaderProgram::useProgram() {
    glUseProgram(program);
}
