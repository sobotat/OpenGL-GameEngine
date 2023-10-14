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
    
    Screen::getInstance()->addOnScreenChangeListener(this);
    Input::getInstance()->addListenerOnKey(this);
    Input::getInstance()->addListenerOnCursor(this);
    onScreenChanged(Screen::getInstance());
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
    if (glfwGetKey(keyInput.window, GLFW_KEY_W) == GLFW_PRESS) position.z -= moveSpeed;            
    if (glfwGetKey(keyInput.window, GLFW_KEY_S) == GLFW_PRESS) position.z += moveSpeed;
    if (glfwGetKey(keyInput.window, GLFW_KEY_D) == GLFW_PRESS) position.x += moveSpeed;
    if (glfwGetKey(keyInput.window, GLFW_KEY_A) == GLFW_PRESS) position.x -= moveSpeed;
    if (glfwGetKey(keyInput.window, GLFW_KEY_SPACE) == GLFW_PRESS) position.y += moveSpeed;
    if (glfwGetKey(keyInput.window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) position.y -= moveSpeed;

    notifyOnCameraChanged();
}

void Camera::onCursorChanged(CursorInput cursorInput) {
    float width = Screen::getInstance()->getWidth();
    float height = Screen::getInstance()->getHeight();

    float alpha = (cursorInput.x - width / 2) * cursorSpeed;
    float phi = (height / 2 - cursorInput.y) * cursorSpeed;
    
    while (alpha > 2 * glm::pi<float>()) {
        alpha -= 2 * glm::pi<float>();
    }
    while (alpha < 0) {
        alpha += 2 * glm::pi<float>();
    }

    // Teleporting Up and Down - Not compatible with Clamping
    while (phi > glm::half_pi<float>()) {
        phi -= glm::pi<float>();
    }
    while (phi < -glm::half_pi<float>()) {
        phi += glm::pi<float>();
    }
    
    // Clamping Up and Down - Not compatible with Teleporting
    // Not using because long wait time if you go over
    // phi = clamp(phi, -glm::half_pi<float>(), glm::half_pi<float>());
    
    target.x = cos(alpha) * cos(phi);
    target.y = sin(phi);
    target.z = sin(alpha) * cos(phi);

    notifyOnCameraChanged();
}
