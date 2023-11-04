#include "Scene.h"

#include <GLFW/glfw3.h>

#include "Application.h"
#include "Screen.h"

void Scene::notifyLightChangedInSceneChanged(shared_ptr<Light> light) {
    int index = 0; 
    for (shared_ptr<LightChangedInSceneListener> listener : lightListeners) {
        listener->onLightChangedInSceneChanged(shared_ptr<Scene>(this), light, index);
        index++;
    }
}

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

void Scene::addLight(const shared_ptr<Light>& light) {
    lights.push_back(light);
    light->addOnLightChangeListener(this);
}

void Scene::onLightChanged(shared_ptr<Light> light) {
    notifyLightChangedInSceneChanged(light);
}

void Scene::addLightChangedInSceneChanged(shared_ptr<LightChangedInSceneListener> listener) {
    lightListeners.push_back(listener);
}

void Scene::clearLightChangedInSceneChanged() {
    lightListeners.clear();
}

vector<shared_ptr<Light>> Scene::getLights() {
    return this->lights;
}

shared_ptr<Actor> Scene::getActor(int index) {
    if (index >= actors.size() || index < 0) return nullptr;
    return actors[index];
}
