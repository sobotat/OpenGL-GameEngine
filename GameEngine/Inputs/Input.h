#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

struct KeyInput {
    GLFWwindow* window;
    int key;
    int scancode;
    int action;
    int mods;
};

struct CursorInput {
    GLFWwindow* window;
    double x;
    double y;
};

struct MouseInput {
    GLFWwindow* window;
    int button;
    int action;
    int mode;
};

class OnKeyListener {
public:
    virtual void notify(KeyInput keyInput) = 0;
};

class OnCursorListener {
public:
    virtual void notify(CursorInput cursorInput) = 0;
};

class OnMouseListener {
public:
    virtual void notify(MouseInput mouseInput) = 0;
};

#pragma once
using namespace std;
class Input
{
protected:
    vector<OnKeyListener*> onKeyListeners;
    vector<OnCursorListener*> onCursorListeners;
    vector<OnMouseListener*> onMouseListeners;

    void notifyOnKey(GLFWwindow* window, int key, int scancode, int action, int mods) const;
    void notifyOnCursor(GLFWwindow* window, double x, double y) const;
    void notifyOnMouse(GLFWwindow* window, int button, int action, int mode) const;
    
public:
    Input(GLFWwindow* window);

    void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) const;
    void onCursor(GLFWwindow* window, double x, double y);
    void onMouse(GLFWwindow* window, int button, int action, int mode);
    
    void addListenerOnKey(OnKeyListener* listener);
    void addListenerOnCursor(OnCursorListener* listener);
    void addListenerOnMouse(OnMouseListener* listener);
};