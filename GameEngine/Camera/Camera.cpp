#include "Camera.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

void Camera::notifyOnCameraChanged() {
    for(CameraListener* listener : listeners) {
        listener->onCameraChanged(this);
    }
}

Camera::Camera() {
    fov = radians(45.0f);
    position = {0, 0, 3};
    target = {0, 0,  -4};
    up = {0, 1, 0};

    Screen* screen = Screen::getInstance();    
    screen->addOnScreenChangeListener(this);
    lastX = screen->getWidth()/2;
    lastY = screen->getHeight()/2;
    
    Input::getInstance()->addListenerOnKey(this);
    Input::getInstance()->addListenerOnCursor(this);
    onScreenChanged(Screen::getInstance());
    notifyOnCameraChanged();
}

mat4 Camera::getView() {
    return lookAt(position, position + target, up);
}

mat4 Camera::getProjection() {
    return projectionMatrix;
}

void Camera::addListenerOnCameraChanged(CameraListener* listener) {
    listeners.push_back(listener);
}

void Camera::onScreenChanged(Screen* screen) {
    projectionMatrix = perspective(fov, screen->getRatio(), 0.1f, 100.0f);
    
    notifyOnCameraChanged();
}

void Camera::onKeyChanged(KeyInput keyInput) {
    if (glfwGetKey(keyInput.window, GLFW_KEY_W) == GLFW_PRESS) {
        position.x += moveSpeed * cos(glm::radians(yaw));
        position.z += moveSpeed * sin(glm::radians(yaw));
    }
    if (glfwGetKey(keyInput.window, GLFW_KEY_S) == GLFW_PRESS) {
        position.x -= moveSpeed * cos(glm::radians(yaw));
        position.z -= moveSpeed * sin(glm::radians(yaw));
    }
    if (glfwGetKey(keyInput.window, GLFW_KEY_A) == GLFW_PRESS) {
        position.x += moveSpeed * sin(glm::radians(yaw));
        position.z -= moveSpeed * cos(glm::radians(yaw));
    }
    if (glfwGetKey(keyInput.window, GLFW_KEY_D) == GLFW_PRESS) {
        position.x -= moveSpeed * sin(glm::radians(yaw));
        position.z += moveSpeed * cos(glm::radians(yaw));
    }
    if (glfwGetKey(keyInput.window, GLFW_KEY_SPACE) == GLFW_PRESS) position.y += moveSpeed;
    if (glfwGetKey(keyInput.window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) position.y -= moveSpeed;

    notifyOnCameraChanged();
}

void Camera::onCursorChanged(CursorInput cursorInput) {
    const double offsetX = (cursorInput.x - lastX) * cursorSpeed;
    const double offsetY = (lastY - cursorInput.y) * cursorSpeed;
    lastX = cursorInput.x;
    lastY = cursorInput.y;

    yaw += offsetX;
    pitch += offsetY;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    
    target.x = float(cos(radians(yaw)) * cos(radians(pitch)));
    target.y = float(sin(radians(pitch)));
    target.z = float(sin(radians(yaw)) * cos(radians(pitch)));

    notifyOnCameraChanged();
}
