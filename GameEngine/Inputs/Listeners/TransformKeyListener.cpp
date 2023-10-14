#include "TransformKeyListener.h"

#include "../../Application.h"
#include "../../Transformations/Location.h"
#include "../../Transformations/Rotation.h"
#include "../../Transformations/Scale.h"

class Actor;

void TransformKeyListener::onLeft() {
    Actor* actor = Application::getInstance()->getScene()->getActor(selectedIndex);
    if (actor == nullptr) return;

    switch (mode) {
    case 'L':
        actor->addTransform(new Location({-.1, 0, 0})); break;
    case 'R':
        actor->addTransform(new Rotation(-.1, {0, 1, 0})); break;
    case 'S':
        actor->addTransform(new Scale({.9, .9, .9})); break;
    }
}

void TransformKeyListener::onRight() {
    Actor* actor = Application::getInstance()->getScene()->getActor(selectedIndex);
    if (actor == nullptr) return;

    switch (mode) {
    case 'L':
        actor->addTransform(new Location({.1, 0, 0})); break;
    case 'R':
        actor->addTransform(new Rotation(.1, {0, 1, 0})); break;
    case 'S':
        actor->addTransform(new Scale({1.1, 1.1, 1.1})); break;
    }
}

void TransformKeyListener::onUp() {
    Actor* actor = Application::getInstance()->getScene()->getActor(selectedIndex);
    if (actor == nullptr) return;

    switch (mode) {
    case 'L':
        actor->addTransform(new Location({0, .1, 0})); break;
    case 'R':
        actor->addTransform(new Rotation(-.1, {1, 0, 0})); break;
    case 'S':
        actor->addTransform(new Scale({1.1, 1.1, 1.1})); break;
    }
}

void TransformKeyListener::onDown() {
    Actor* actor = Application::getInstance()->getScene()->getActor(selectedIndex);
    if (actor == nullptr) return;

    switch (mode) {
    case 'L':
        actor->addTransform(new Location({0, -.1, 0})); break;
    case 'R':
        actor->addTransform(new Rotation(.1, {1, 0, 0})); break;
    case 'S':
        actor->addTransform(new Scale({.9, .9, .9})); break;
    }
}

void TransformKeyListener::onKeyChanged(KeyInput keyInput) {
    if (keyInput.action == 0) return;

    int num = keyInput.key - 48;
    if (num >= 0 && num <= 9) {
        printf("Set current to [%d]\n", num);
        selectedIndex = num;
        return;
    }

    switch (keyInput.key) {
    case GLFW_KEY_LEFT:
        onLeft(); break;
    case GLFW_KEY_RIGHT:
        onRight(); break;
    case GLFW_KEY_UP:
        onUp(); break;
    case GLFW_KEY_DOWN:
        onDown(); break;
    case GLFW_KEY_L:
        printf("Mode set to Move\n");
        mode = 'L';
        break;
    case GLFW_KEY_R:
        printf("Mode set to Rotate\n");
        mode = 'R';
        break;
    case GLFW_KEY_T:
        printf("Mode set to Scale\n");
        mode = 'S';
        break;
    }
}
