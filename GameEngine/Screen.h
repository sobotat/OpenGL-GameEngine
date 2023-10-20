#pragma once
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

#include "ScreenListener.hpp"
#include "Inputs/Input.h"

using namespace std;

class ScreenListener;

class Screen : public OnMouseListener {
protected:
    static shared_ptr<Screen> instance;

    vector<ScreenListener*> listeners;
    
    string title = "ZPG";
    int width = 1920;
    int height = 1080;
    float ratio = 1;
    GLFWwindow* window = nullptr;

    bool isFocus = true;
    bool isIconified = false;
    bool isMouseLocked = false;

    void notifyScreenChanged();
    
public:
    ~Screen();
    void init();
    
    static shared_ptr<Screen> getInstance(); 
    GLFWwindow* getWindow();
    float getWidth();
    float getHeight();
    float getRatio();
    bool getIsMouseLocked();

    bool getIsIconified();
    
    void onFocus(GLFWwindow* window, int focused);
    void onIconify(GLFWwindow* window, int iconified);
    void onSizeChanged(GLFWwindow* window, int width, int height);

    void onMouseChanged(MouseInput mouseInput) override;

    void addOnScreenChangeListener(ScreenListener* listener);
};
