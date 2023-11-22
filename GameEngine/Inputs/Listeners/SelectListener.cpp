#include "SelectListener.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_projection.hpp>

#include "Application.h"
#include "Screen.h"

void SelectListener::notifyOnSelected() const {
    SelectResult result;
    result.found = depth != 1;
    result.x = lastX;
    result.y = lastY;
    result.index = index;
    result.depth = depth;
    result.position = position;
    result.color = vec4(color[0], color[1], color[2], color[3]);

    for (OnSelectListener* listener : listeners) {
        listener->OnSelected(result);
    }
}

void SelectListener::onMouseChanged(MouseInput mouseInput) {

    if (mouseInput.button != GLFW_MOUSE_BUTTON_1 || mouseInput.action != GLFW_PRESS)
        return;

    const shared_ptr<Screen> screen = Screen::getInstance();
    const int newY = static_cast<int>(screen->getHeight()) - lastY;
 
    glReadPixels(lastX, newY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    glReadPixels(lastX, newY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glReadPixels(lastX, newY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    const shared_ptr<Camera> camera = Application::getInstance()->getCamera(); 
    const vec3 screenX = vec3(lastX, newY, depth);
    const mat4 view = camera->getView();
    const mat4 projection = camera->getProjection();
    const vec4 viewPort = vec4(0, 0, screen->getWidth(), screen->getHeight());
    position = unProject(screenX, view, projection, viewPort);
    
    printf("Pixel [%d,%d] [%f,%f,%f] - color 0x%02hhx%02hhx%02hhx%02hhx, depth %f, index %u\n",
                  lastX, lastY, position.x, position.y, position.z, color[0], color[1], color[2], color[3], depth, index);

    notifyOnSelected();
}

void SelectListener::onCursorChanged(CursorInput cursorInput) {
    lastX = static_cast<int>(cursorInput.x);
    lastY = static_cast<int>(cursorInput.y);
}

void SelectListener::addListenerOnSelected(OnSelectListener* listener) {
    listeners.push_back(listener);
}
