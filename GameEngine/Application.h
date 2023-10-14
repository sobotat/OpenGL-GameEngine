
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>

#include "Scene.h"
#include "Shaders/ShaderProgram.h"

class Application {
protected:
    static Application* instance_;

    vector<ShaderProgram*> shaderPrograms;
    vector<Shader*> shaders;
    
    Scene* scene = nullptr;
    Camera* camera = nullptr;

    void onExit();
    
public:
    ~Application();
    static Application* getInstance();
    void init();
    void createShaders();
    void createModels();
    void run();

    Scene* getScene();    
    Camera* getCamera();
};
