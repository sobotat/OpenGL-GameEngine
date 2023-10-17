#include "Input.h"

#include <cstdio>
#include <GLFW/glfw3.h>
#include "../GLFWCallbacks/InputGLFWCallbacks.hpp"

Input* Input::instance = new Input();

void Input::init(GLFWwindow* window) {
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_callback);
    glfwSetMouseButtonCallback(window, button_callback);
}

Input* Input::getInstance() {
    return instance;
}

void Input::addListenerOnKey(shared_ptr<OnKeyListener> listener) {
    onKeyListeners.push_back(listener);
}

void Input::addListenerOnCursor(shared_ptr<OnCursorListener> listener) {
    onCursorListeners.push_back(listener);
}

void Input::addListenerOnMouse(shared_ptr<OnMouseListener> listener) {
    onMouseListeners.push_back(listener);
}

void Input::onKey(GLFWwindow* window, int key, int scancode, int action, int mods) const {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    //printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
    notifyOnKey(window, key, scancode, action, mods);
}

void Input::onCursor(GLFWwindow* window, double x, double y) {    
    notifyOnCursor(window, x, y);
}

void Input::onMouse(GLFWwindow* window, int button, int action, int mode) {
    //if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
    notifyOnMouse(window, button, action, mode);
}

void Input::notifyOnKey(GLFWwindow* window, int key, int scancode, int action, int mods) const {
    
    KeyInput input;
    input.window = window;
    input.key = key;
    input.scancode = scancode;
    input.action = action;
    input.mods = mods;
    
    for (shared_ptr<OnKeyListener> listener : onKeyListeners) {
        listener->onKeyChanged(input);    
    }
}

void Input::notifyOnCursor(GLFWwindow* window, double x, double y) const {

    CursorInput input;
    input.window = window;
    input.x = x;
    input.y = y;

    for (shared_ptr<OnCursorListener> listener : onCursorListeners) {
        listener->onCursorChanged(input);
    } 
}

void Input::notifyOnMouse(GLFWwindow* window, int button, int action, int mode) const {

    MouseInput input;
    input.window = window;
    input.button = button;
    input.action = action;
    input.mode = mode;

    for (shared_ptr<OnMouseListener> listener : onMouseListeners) {
        listener->onMouseChanged(input);
    }
}

Input::~Input() {
    onKeyListeners.clear();
    onCursorListeners.clear();
    onMouseListeners.clear();
}
