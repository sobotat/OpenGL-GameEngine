#include "Screen.h"

#include <cstdlib>

#include "GLFWCallbacks/WindowGLFWCallbacks.hpp"

Screen* Screen::instance = nullptr;

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
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetWindowIconifyCallback(window, window_iconify_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
}

Screen* Screen::getInstance() {
    if (instance == nullptr) {
        instance = new Screen();
    }
    return instance;
}

GLFWwindow* Screen::getWindow() {
    return window;
}

void Screen::onFocus(GLFWwindow* window, int focused) {
    isFocus = focused == 1 ? true : false;
    printf("Focus [%d]\n", isFocus);
}

void Screen::onIconify(GLFWwindow* window, int iconified) {
    isIconified = iconified == 1 ? true : false;
    printf("Iconified [%d]\n", isIconified);
}

void Screen::onSizeChanged(GLFWwindow* window, int width, int height) {
    this->width = width;
    this->height = height;
    this->ratio = float(width) / float(height);
    
    printf("Size [%d, %d]\n", width, height);
    glViewport(0, 0, width, height);
}
