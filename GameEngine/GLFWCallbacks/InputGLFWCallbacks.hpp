#pragma once
#include <GLFW/glfw3.h>
#include "../Application.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Application::getInstance()->getInput()->onKey(window, key, scancode, action, mods);
}

static void cursor_callback(GLFWwindow* window, double x, double y) { 
    Application::getInstance()->getInput()->onCursor(window, x, y);
}

static void button_callback(GLFWwindow* window, int button, int action, int mode) {
    Application::getInstance()->getInput()->onMouse(window, button, action, mode);
}
