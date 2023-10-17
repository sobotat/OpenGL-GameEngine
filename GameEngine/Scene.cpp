#include "Scene.h"

#include <GLFW/glfw3.h>

#include "Screen.h"

Scene::~Scene() {
    actors.clear();
}

void Scene::draw() {
    // clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (const shared_ptr<Actor>& actor : actors) {        
        actor->tick();
    }
    
    for (const shared_ptr<Actor>& actor : actors) {
        actor->draw();
    }

    // update other events like input handling
    glfwPollEvents();
    // put the stuff we’ve been drawing onto the display
    glfwSwapBuffers(Screen::getInstance()->getWindow());
}

void Scene::addActor(const shared_ptr<Actor>& actor) {
    actors.push_back(actor);
}

shared_ptr<Actor> Scene::getActor(int index) {
    if (index >= actors.size() || index < 0) return nullptr;
    return actors[index];
}
