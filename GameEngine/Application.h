
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>

#include "Scene.h"
#include "Inputs/Input.h"
#include "Shaders/FragmentShader.h"
#include "Shaders/VertexShader.h"

class Application {
protected:
    static Application* instance_;
    
    Input* input = nullptr;
    Scene* scene = nullptr;

    void onExit();
    
public:
    static Application* getInstance();
    void init();
    void createShaders();
    void createModels();
    void run();
    Input* getInput();
};