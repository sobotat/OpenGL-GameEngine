
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>

#include "Scene.h"

class Application {
protected:
    static Application* instance_;
    
    Scene* scene = nullptr;

    void onExit();
    
public:
    static Application* getInstance();
    void init();
    void createShaders();
    void createModels();
    void run();
};