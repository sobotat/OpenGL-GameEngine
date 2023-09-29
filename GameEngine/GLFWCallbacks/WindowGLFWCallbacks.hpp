#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Application.h"

static void window_focus_callback(GLFWwindow* window, int focused) {
    Screen::getInstance()->onFocus(window, focused);
}

static void window_iconify_callback(GLFWwindow* window, int iconified) {
    Screen::getInstance()->onIconify(window, iconified);
}

static void window_size_callback(GLFWwindow* window, int width, int height) {
    Screen::getInstance()->onSizeChanged(window, width, height);
}
