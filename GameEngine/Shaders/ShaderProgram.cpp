#include "ShaderProgram.h"

#include <glm/gtc/type_ptr.hpp>

#include "../Application.h"
#include "../Lights/Light.h"

ShaderProgram::ShaderProgram(vector<shared_ptr<Shader>> shaders) {
    this->shaders = move(shaders);

    Application::getInstance()->addOnActiveSceneChanged(this);
    shared_ptr<Camera> camera = Application::getInstance()->getCamera();
    camera->addListenerOnCameraChanged(this);
    onCameraChanged(camera);
    
    printf("Setting Shader Program ...\n");
    program = glCreateProgram();
    for (shared_ptr<Shader>& shader : this->shaders) {
        shader->attach(program);
    }
    glLinkProgram(program);

    printf("Checking Shaders ...\n");
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
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

void ShaderProgram::useProgram() {
    glUseProgram(program);
    
    setPropertyMatrix(viewMatrix, "viewMatrix");
    setPropertyMatrix(projectionMatrix, "projectionMatrix");
    setPropertyVec3(cameraPosition, "cameraPosition");
}

void ShaderProgram::resetProgram() {
    glUseProgram(0);
}

void ShaderProgram::setPropertyMatrix(mat4 value, string property) {
    const GLint propertyId = glGetUniformLocation(program, property.c_str());
    glProgramUniformMatrix4fv(program,propertyId , 1, GL_FALSE, value_ptr(value));
}

void ShaderProgram::setPropertyVec3(vec3 value, string property) {
    const GLint propertyId = glGetUniformLocation(program, property.c_str());
    glProgramUniform3fv(program,propertyId, 1, value_ptr(value));
}

void ShaderProgram::setPropertyVec4(vec4 value, string property) {
    const GLint propertyId = glGetUniformLocation(program, property.c_str());
    glProgramUniform4fv(program,propertyId, 1, value_ptr(value));
}

void ShaderProgram::onCameraChanged(shared_ptr<Camera> camera) {
    viewMatrix = camera->getView();
    projectionMatrix = camera->getProjection();
    cameraPosition = camera->getPosition();
}

void ShaderProgram::onActiveSceneChanged(shared_ptr<Scene> scene) {
    vector<shared_ptr<Light>> lights = scene->getLights();

    if(lights.empty()) {
        setPropertyVec3({0,0,0}, "lightPosition");
        setPropertyVec4({0,0,0, 0}, "lightColor");
        return;
    }
    
    for (auto& light : lights) {
        setPropertyVec3(light->getPosition(), "lightPosition");
        setPropertyVec4(light->getColor(), "lightColor");
    }
}

