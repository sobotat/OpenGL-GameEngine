
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

static void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

static void window_focus_callback(GLFWwindow* window, int focused) {
    printf("window_focus_callback \n");
}

static void window_iconify_callback(GLFWwindow* window, int iconified) {
    printf("window_iconify_callback \n");
}

static void window_size_callback(GLFWwindow* window, int width, int height) {
    printf("resize %d, %d \n", width, height);
    glViewport(0, 0, width, height);
}