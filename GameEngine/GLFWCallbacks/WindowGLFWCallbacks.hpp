#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Application.h"

static void window_focus_callback(GLFWwindow* window, int focused) {
    Application::getInstance()->getScreen()->onFocus(window, focused);
}

static void window_iconify_callback(GLFWwindow* window, int iconified) {
    Application::getInstance()->getScreen()->onIconify(window, iconified);
}

static void window_size_callback(GLFWwindow* window, int width, int height) {
    Application::getInstance()->getScreen()->onSizeChanged(window, width, height);
}
