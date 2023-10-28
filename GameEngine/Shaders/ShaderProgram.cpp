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
}

void ShaderProgram::resetProgram() {
    glUseProgram(0);
}

void ShaderProgram::setProperty(mat4 value, string property) {
    const GLint propertyId = glGetUniformLocation(program, property.c_str());
    glProgramUniformMatrix4fv(program,propertyId , 1, GL_FALSE, value_ptr(value));
}

void ShaderProgram::setProperty(vec3 value, string property) {
    const GLint propertyId = glGetUniformLocation(program, property.c_str());
    glProgramUniform3fv(program,propertyId, 1, value_ptr(value));
}

void ShaderProgram::setProperty(vec4 value, string property) {
    const GLint propertyId = glGetUniformLocation(program, property.c_str());
    glProgramUniform4fv(program,propertyId, 1, value_ptr(value));
}

void ShaderProgram::setProperty(float value, string property) {
    const GLint propertyId = glGetUniformLocation(program, property.c_str());
    glProgramUniform1f(program, propertyId, value);
}

void ShaderProgram::setProperty(int value, string property) {
    const GLint propertyId = glGetUniformLocation(program, property.c_str());
    glProgramUniform1i(program, propertyId, value);
}

void ShaderProgram::onCameraChanged(shared_ptr<Camera> camera) {
    setProperty(camera->getView(), "viewMatrix");
    setProperty(camera->getProjection(), "projectionMatrix");
    setProperty(camera->getPosition(), "cameraPosition");
}

void ShaderProgram::onActiveSceneChanged(shared_ptr<Scene> scene) {
    vector<shared_ptr<Light>> lights = scene->getLights();

    if(lights.empty()) {
        setProperty({0,0,0}, "lightPosition");
        setProperty({0,0,0, 0}, "lightColor");
        setProperty(0, "lightDimmingFactor");
        return;
    }
    
    for (auto& light : lights) {
        setProperty(light->getPosition(), "lightPosition");
        setProperty(light->getColor(), "lightColor");
        setProperty(light->getDimmingFactor(), "lightDimmingFactor");
    }
}

void ShaderProgram::onLightChangedInSceneChanged(shared_ptr<Scene> scene, shared_ptr<Light> light) {
    vector<shared_ptr<Light>> lights = scene->getLights();

    if(lights.empty()) {
        setProperty({0,0,0}, "lightPosition");
        setProperty({0,0,0, 0}, "lightColor");
        setProperty(0, "lightDimmingFactor");
        return;
    }
    
    for (auto& light : lights) {
        setProperty(light->getPosition(), "lightPosition");
        setProperty(light->getColor(), "lightColor");
        setProperty(light->getDimmingFactor(), "lightDimmingFactor");
    }
}

