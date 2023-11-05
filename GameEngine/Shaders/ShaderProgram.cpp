#include "ShaderProgram.h"

#include <glm/gtc/type_ptr.hpp>

#include "../Application.h"
#include "../Lights/DirectionalLight.h"
#include "../Lights/Light.h"
#include "../Lights/PointLight.h"
#include "../Lights/SpotLight.h"

enum LightType {
    POINT, SPOT, DIRECTIONAL
};

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
        setProperty(0, "lights[0].type");
        setProperty({0,0,0}, "lights[0].position");
        setProperty({0,0,0, 0}, "lights[0].color");
        setProperty(0, "lights[0].dimmingFactor");
        setProperty(0, "lights[0].diffuseFactor");
        setProperty(1, "numberOfLights");
        return;
    }
    
    for (int index = 0; index < lights.size(); index++) {
        shared_ptr<Light>& light = lights.at(index);

        setProperty(-1, "lights[" + std::to_string(index) + "].type");

        shared_ptr<DirectionalLight> directionalLight = dynamic_pointer_cast<DirectionalLight>(light);
        if (directionalLight) {
            setProperty(LightType::DIRECTIONAL, "lights[" + std::to_string(index) + "].type");
            setProperty(directionalLight->getDirection(), "lights[" + std::to_string(index) + "].direction");
        }
        
        shared_ptr<PointLight> pointLight = dynamic_pointer_cast<PointLight>(light);
        if (pointLight) {
            setProperty(LightType::POINT, "lights[" + std::to_string(index) + "].type");
            setProperty(pointLight->getPosition(), "lights[" + std::to_string(index) + "].position");
            setProperty(pointLight->getDimmingFactor(), "lights[" + std::to_string(index) + "].dimmingFactor");

            shared_ptr<SpotLight> spotLight = dynamic_pointer_cast<SpotLight>(light);
            if (spotLight) {
                setProperty(LightType::SPOT, "lights[" + std::to_string(index) + "].type");
                setProperty(spotLight->getDirection(), "lights[" + std::to_string(index) + "].direction");
                setProperty(spotLight->getAngle(), "lights[" + std::to_string(index) + "].angle");
                setProperty(spotLight->getFadeStartAngle(), "lights[" + std::to_string(index) + "].fadeStartAngle");
            }
        }
        
        setProperty(light->getColor(), "lights[" + std::to_string(index) + "].color");        
        setProperty(light->getDiffuseFactor(), "lights[" + std::to_string(index) + "].diffuseFactor");
    }
    setProperty(static_cast<int>(lights.size()), "numberOfLights");
}

void ShaderProgram::onLightChangedInSceneChanged(shared_ptr<Scene> scene, shared_ptr<Light>& light, int index) {
    const vector<shared_ptr<Light>> lights = scene->getLights();

    setProperty(-1, "lights[" + std::to_string(index) + "].type");

    if(lights.empty()) {
        setProperty(LightType::POINT, "lights[" + std::to_string(index) + "].type");
        setProperty({0,0,0}, "lights[0].position");
        setProperty({0,0,0, 0}, "lights[0].color");
        setProperty(0, "lights[0].dimmingFactor");
        setProperty(0, "lights[0].diffuseFactor");
        setProperty(1, "numberOfLights");
        return;
    }

    shared_ptr<DirectionalLight> directionalLight = dynamic_pointer_cast<DirectionalLight>(light);
    if (directionalLight) {
        setProperty(LightType::DIRECTIONAL, "lights[" + std::to_string(index) + "].type");
        setProperty(directionalLight->getDirection(), "lights[" + std::to_string(index) + "].direction");
    }
    
    shared_ptr<PointLight> pointLight = dynamic_pointer_cast<PointLight>(light);
    if (pointLight) {
        setProperty(LightType::POINT, "lights[" + std::to_string(index) + "].type");
        setProperty(pointLight->getPosition(), "lights[" + std::to_string(index) + "].position");
        setProperty(pointLight->getDimmingFactor(), "lights[" + std::to_string(index) + "].dimmingFactor");

        shared_ptr<SpotLight> spotLight = dynamic_pointer_cast<SpotLight>(light);
        if (spotLight) {
            setProperty(LightType::SPOT, "lights[" + std::to_string(index) + "].type");
            setProperty(spotLight->getDirection(), "lights[" + std::to_string(index) + "].direction");
            setProperty(spotLight->getAngle(), "lights[" + std::to_string(index) + "].angle");
        }
    }
    
    setProperty(light->getColor(), "lights[" + std::to_string(index) + "].color");    
    setProperty(light->getDiffuseFactor(), "lights[" + std::to_string(index) + "].diffuseFactor");
    setProperty(static_cast<int>(lights.size()), "numberOfLights");
}

