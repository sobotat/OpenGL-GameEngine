
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>

#include "Scene.h"
#include "Screen.h"
#include "Inputs/Input.h"
#include "Shaders/FragmentShader.h"
#include "Shaders/VertexShader.h"

class Application {
protected:
    static Application* instance_;
    
    Input* input = nullptr;
    Scene* scene = nullptr;
    Screen* screen = nullptr;

    void onExit();
    
public:
    static Application* getInstance();
    void init();
    void createShaders();
    void createModels();
    void run();
    GLFWwindow* getWindow();
    Input* getInput();
    Screen* getScreen();
};

static void error_callback(int error, const char* description) {
    fputs(description, stderr);
}