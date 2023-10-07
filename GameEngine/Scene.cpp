#include "Scene.h"

#include <GLFW/glfw3.h>

#include "Screen.h"

Scene::~Scene() {
    for (Actor* actor : actors) {
        delete actor;
    }
    actors.clear();
}

void Scene::draw() {
    // clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (Actor* actor : actors) {        
        actor->tick();
    }
    
    for (Actor* actor : actors) {
        actor->draw();
    }

    // update other events like input handling
    glfwPollEvents();
    // put the stuff we’ve been drawing onto the display
    glfwSwapBuffers(Screen::getInstance()->getWindow());
}

void Scene::addActor(Actor* actor) {
    actors.push_back(actor);
}
