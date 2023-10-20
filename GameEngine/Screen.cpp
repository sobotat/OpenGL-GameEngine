#include "Screen.h"
#include "Screen.h"

#include <cstdlib>

#include "GLFWCallbacks/WindowGLFWCallbacks.hpp"

shared_ptr<Screen> Screen::instance = nullptr;

void Screen::notifyScreenChanged() {
    for(ScreenListener* listener : listeners) {
        listener->onScreenChanged(this);
    }
}

Screen::~Screen() {
    listeners.clear();
}

void Screen::init() {    
    ratio = float(width) / float(height);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwGetFramebufferSize(window, &width, &height);
    
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetWindowIconifyCallback(window, window_iconify_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    notifyScreenChanged();

    Input::getInstance()->addListenerOnMouse(this);
}

shared_ptr<Screen> Screen::getInstance() {
    if (instance == nullptr) {
        instance = make_shared<Screen>();
    }
    return instance;
}

GLFWwindow* Screen::getWindow() {
    return window;
}

float Screen::getWidth() {
    return width;
}

float Screen::getHeight() {
    return height;
}

float Screen::getRatio() {
    return ratio;
}

bool Screen::getIsMouseLocked() {
    return isMouseLocked;
}

bool Screen::getIsIconified() {
    return isIconified;
}

void Screen::onFocus(GLFWwindow* window, int focused) {
    isFocus = focused == 1 ? true : false;
    printf("Focus [%d]\n", isFocus);
    notifyScreenChanged();
}

void Screen::onIconify(GLFWwindow* window, int iconified) {
    isIconified = iconified == 1 ? true : false;
    printf("Iconified [%d]\n", isIconified);
    notifyScreenChanged();
}

void Screen::onSizeChanged(GLFWwindow* window, int width, int height) {
    if (height == 0) return;
    
    this->width = width;
    this->height = height;
    this->ratio = float(width) / float(height);
    
    printf("Size [%d, %d]\n", width, height);
    glViewport(0, 0, width, height);
    notifyScreenChanged();
}

void Screen::onMouseChanged(MouseInput mouseInput) {
    if (mouseInput.button == GLFW_MOUSE_BUTTON_2) {
        if (mouseInput.action == GLFW_PRESS) {
            shared_ptr<Camera> camera = Application::getInstance()->getCamera();
            glfwSetCursorPos(window, camera->getLastX(), camera->getLastY());
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            isMouseLocked = true;
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            isMouseLocked = false;
        }
    }
}

void Screen::addOnScreenChangeListener(ScreenListener* listener) {
    listeners.push_back(listener);
}
