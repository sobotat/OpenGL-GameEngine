#pragma once
#include <memory>
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
    virtual ~OnKeyListener() = default;
    virtual void onKeyChanged(KeyInput keyInput) = 0;
};

class OnCursorListener {
public:
    virtual ~OnCursorListener() = default;
    virtual void onCursorChanged(CursorInput cursorInput) = 0;
};

class OnMouseListener {
public:
    virtual ~OnMouseListener() = default;
    virtual void onMouseChanged(MouseInput mouseInput) = 0;
};

#pragma once
using namespace std;
class Input
{
protected:
    static Input* instance;
    
    vector<shared_ptr<OnKeyListener>> onKeyListeners;
    vector<shared_ptr<OnCursorListener>> onCursorListeners;
    vector<shared_ptr<OnMouseListener>> onMouseListeners;

    void notifyOnKey(GLFWwindow* window, int key, int scancode, int action, int mods) const;
    void notifyOnCursor(GLFWwindow* window, double x, double y) const;
    void notifyOnMouse(GLFWwindow* window, int button, int action, int mode) const;
    
public:
    ~Input();
    void init(GLFWwindow* window);

    static Input* getInstance();

    void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) const;
    void onCursor(GLFWwindow* window, double x, double y);
    void onMouse(GLFWwindow* window, int button, int action, int mode);
    
    void addListenerOnKey(shared_ptr<OnKeyListener> listener);
    void addListenerOnCursor(shared_ptr<OnCursorListener> listener);
    void addListenerOnMouse(shared_ptr<OnMouseListener> listener);
};