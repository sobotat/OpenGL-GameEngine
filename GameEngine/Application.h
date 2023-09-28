
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
    
    int width = 800;
    int height = 800;
    float ratio;
    GLFWwindow* window;
    
    Input* input;
    Scene* scene;

    void onExit();
    
public:
    static Application* getInstance();
    Application();
    void init();
    void createShaders();
    void createModels();
    void run();
    GLFWwindow* getWindow();
    Input* getInput();     
};
