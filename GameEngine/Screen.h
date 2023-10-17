#pragma once
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

#include "ScreenListener.hpp"

using namespace std;

class ScreenListener;

class Screen {
protected:
    static shared_ptr<Screen> instance;

    vector<shared_ptr<ScreenListener>> listeners;
    
    string title = "ZPG";
    int width = 1920;
    int height = 1080;
    float ratio = 1;
    GLFWwindow* window = nullptr;

    bool isFocus = true;
    bool isIconified = false;

    void notifyScreenChanged();
    
public:
    ~Screen();
    void init();
    
    static shared_ptr<Screen> getInstance(); 
    GLFWwindow* getWindow();
    float getWidth();
    float getHeight();
    float getRatio();
    
    void onFocus(GLFWwindow* window, int focused);
    void onIconify(GLFWwindow* window, int iconified);
    void onSizeChanged(GLFWwindow* window, int width, int height);

    void addOnScreenChangeListener(const shared_ptr<ScreenListener>& listener);
};
