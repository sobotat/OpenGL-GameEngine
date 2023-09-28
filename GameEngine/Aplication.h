
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>

#include "Inputs/Input.h"
#include "Shaders/FragmentShader.h"
#include "Shaders/VertexShader.h"

class Aplication {
protected:
    static Aplication* instance_;
    
    int width = 800;
    int height = 800;
    float ratio;
    GLFWwindow* window;
    Input* input;
    
public:
    static Aplication* getInstance();
    Aplication();
    void init();
    void createShaders();
    void createModels();
    void run();
    GLFWwindow* getWindow();
    Input* getInput();     
};
