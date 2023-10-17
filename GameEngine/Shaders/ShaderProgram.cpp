#include "ShaderProgram.h"

#include <glm/gtc/type_ptr.hpp>

#include "../Application.h"

ShaderProgram::ShaderProgram(vector<shared_ptr<Shader>> shaders) {
    this->shaders = move(shaders);
    
    printf("Setting Shader Program ...\n");
    program = glCreateProgram();
    for (shared_ptr<Shader>& shader : this->shaders) {
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
        fprintf(stderr, "\033[1;31mLinker failure: %s \033[0m\n", strInfoLog);
        delete[] strInfoLog;
        exit(EXIT_FAILURE);
    }
    printf("\033[1;32mShader Program Set\033[0m\n");
}

ShaderProgram::~ShaderProgram() {
    shaders.clear();
}

void ShaderProgram::initCameraListener() {
    shared_ptr<Camera> camera = Application::getInstance()->getCamera();
    camera->addListenerOnCameraChanged(shared_from_this());
    onCameraChanged(camera);
}

void ShaderProgram::useProgram() {
    glUseProgram(program);
    
    setPropertyMatrix(viewMatrix, "viewMatrix");
    setPropertyMatrix(projectionMatrix, "projectionMatrix");
}

void ShaderProgram::resetProgram() {
    glUseProgram(0);
}

void ShaderProgram::setPropertyMatrix(mat4 value, string property) {
    const GLint propertyId = glGetUniformLocation(program, property.c_str());
    glUniformMatrix4fv(propertyId , 1, GL_FALSE, value_ptr(value));
}

void ShaderProgram::onCameraChanged(shared_ptr<Camera> camera) {
    viewMatrix = camera->getView();
    projectionMatrix = camera->getProjection();
}

