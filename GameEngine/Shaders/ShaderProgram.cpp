#include "ShaderProgram.h"

#include <glm/gtc/type_ptr.hpp>

#include "../Application.h"

ShaderProgram::ShaderProgram(vector<Shader*> shaders) {
    this->shaders = move(shaders);

    Camera* camera = Application::getInstance()->getCamera();
    camera->addListenerOnCameraChanged(this);
    onCameraChanged(camera);
    
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

ShaderProgram::~ShaderProgram() {
    shaders.clear();
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

void ShaderProgram::onCameraChanged(Camera* camera) {
    viewMatrix = camera->getView();
    projectionMatrix = camera->getProjection();
}

