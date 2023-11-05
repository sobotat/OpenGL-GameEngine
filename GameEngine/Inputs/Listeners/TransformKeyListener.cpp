#include "TransformKeyListener.h"

#include "../../Application.h"
#include "../../Lights/PointLight.h"
#include "../../Transformations/Location.h"
#include "../../Transformations/Rotation.h"
#include "../../Transformations/Scale.h"

class Actor;

void TransformKeyListener::onLeft() const {
    if (selectingActors) {
        const shared_ptr<Actor> actor = Application::getInstance()->getScene()->getActor(selectedIndex);
        if (actor == nullptr) return;

        switch (mode) {
        case 'L':
            actor->addTransform(make_shared<Location>(vec3{-.1, 0, 0})); break;
        case 'R':
            actor->addTransform(make_shared<Rotation>(-1, vec3{0, 1, 0})); break;
        case 'S':
            actor->addTransform(make_shared<Scale>(vec3{.9, .9, .9})); break;
        default: break;
        }
    } else {
        const shared_ptr<Light> light = Application::getInstance()->getScene()->getLight(selectedIndex);
        if (light == nullptr) return;

        const shared_ptr<PointLight> pointLight = dynamic_pointer_cast<PointLight>(light);
        if (pointLight) {
            vec3 position = pointLight->getPosition();
            position.x -= .5f;
            pointLight->setPosition(position);
        }
    }
}

void TransformKeyListener::onRight() const {
    if (selectingActors) {
        const shared_ptr<Actor> actor = Application::getInstance()->getScene()->getActor(selectedIndex);
        if (actor == nullptr) return;

        switch (mode) {
        case 'L':
            actor->addTransform(make_shared<Location>(vec3{.1, 0, 0})); break;
        case 'R':
            actor->addTransform(make_shared<Rotation>(1, vec3{0, 1, 0})); break;
        case 'S':
            actor->addTransform(make_shared<Scale>(vec3{1.1, 1.1, 1.1})); break;
        default: break;
        }
    } else {
        const shared_ptr<Light> light = Application::getInstance()->getScene()->getLight(selectedIndex);
        if (light == nullptr) return;

        const shared_ptr<PointLight> pointLight = dynamic_pointer_cast<PointLight>(light);
        if (pointLight) {
            vec3 position = pointLight->getPosition();
            position.x += .5f;
            pointLight->setPosition(position);
        }
    }
}

void TransformKeyListener::onUp() const {
    if (selectingActors) {
        const shared_ptr<Actor> actor = Application::getInstance()->getScene()->getActor(selectedIndex);
        if (actor == nullptr) return;

        switch (mode) {
        case 'L':
            actor->addTransform(make_shared<Location>(vec3{0, .1, 0})); break;
        case 'R':
            actor->addTransform(make_shared<Rotation>(-1, vec3{1, 0, 0})); break;
        case 'S':
            actor->addTransform(make_shared<Scale>(vec3{1.1, 1.1, 1.1})); break;
        default: break;
        }
    } else {
        const shared_ptr<Light> light = Application::getInstance()->getScene()->getLight(selectedIndex);
        if (light == nullptr) return;

        const shared_ptr<PointLight> pointLight = dynamic_pointer_cast<PointLight>(light);
        if (pointLight) {
            vec3 position = pointLight->getPosition();
            position.y += .5f;
            pointLight->setPosition(position);
        }
    }
}

void TransformKeyListener::onDown() const {
    if (selectingActors) {
        const shared_ptr<Actor> actor = Application::getInstance()->getScene()->getActor(selectedIndex);
        if (actor == nullptr) return;

        switch (mode) {
        case 'L':
            actor->addTransform(make_shared<Location>(vec3{0, -.1, 0})); break;
        case 'R':
            actor->addTransform(make_shared<Rotation>(1, vec3{1, 0, 0})); break;
        case 'S':
            actor->addTransform(make_shared<Scale>(vec3{.9, .9, .9})); break;
        default: break;
        }
    } else {
        const shared_ptr<Light> light = Application::getInstance()->getScene()->getLight(selectedIndex);
        if (light == nullptr) return;

        const shared_ptr<PointLight> pointLight = dynamic_pointer_cast<PointLight>(light);
        if (pointLight) {
            vec3 position = pointLight->getPosition();
            position.y -= .5f;
            pointLight->setPosition(position);
        }
    }
}

void TransformKeyListener::onKeyChanged(KeyInput keyInput) {
    if (keyInput.action == 0) return;

    const int num = keyInput.key - 48;
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
    case GLFW_KEY_P:
        printf(selectingActors ? "Selecting Lights\n" : "Selecting Actors\n");
        selectingActors = !selectingActors;
        break;
    default: break;
    }
}
