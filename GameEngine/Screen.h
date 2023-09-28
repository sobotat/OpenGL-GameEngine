#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

using namespace std;
class Screen {
protected:
    string title = "ZPG";
    int width = 800;
    int height = 800;
    float ratio;
    GLFWwindow* window;

    bool isFocus = true;
    bool isIconified = false;
    
public:
    Screen();
    GLFWwindow* getWindow();
    
    void onFocus(GLFWwindow* window, int focused);
    void onIconify(GLFWwindow* window, int iconified);
    void onSizeChanged(GLFWwindow* window, int width, int height);
};
