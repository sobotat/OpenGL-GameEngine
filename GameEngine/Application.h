
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>

#include "Scene.h"
#include "Shaders/ShaderProgram.h"

class Application {
protected:
    static shared_ptr<Application> instance_;

    vector<shared_ptr<ShaderProgram>> shaderPrograms;
    vector<shared_ptr<Shader>> shaders;
    
    shared_ptr<Scene> scene = nullptr;
    shared_ptr<Camera> camera = nullptr;

    void onExit();
    
public:
    ~Application();
    static shared_ptr<Application> getInstance();
    void init();
    void createShaders();
    void createModels();
    void run();

    shared_ptr<Scene> getScene();    
    shared_ptr<Camera> getCamera();
};
