#include "Scene.h"

#include <GLFW/glfw3.h>

#include "Application.h"
#include "Screen.h"
#include "Meshes/CubeMesh.h"
#include "Shaders\Materials\Texture\CubeMapTexture.h"

void Scene::notifyLightChangedInSceneChanged(shared_ptr<Light> light) {
    int index = std::distance(lights.begin(), std::find_if(lights.begin(), lights.end(), [&](std::shared_ptr<Light> l) { return l.get() == light.get(); })); 
    for (shared_ptr<LightChangedInSceneListener> listener : lightListeners) {
        listener->onLightChangedInSceneChanged(shared_from_this(), light, index);
    }
}

Scene::~Scene() {
    actors.clear();
}

void Scene::draw() {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    if(skybox) {
        skybox->draw();
    }
    
    glClear(GL_DEPTH_BUFFER_BIT);
    
    for (const shared_ptr<Actor>& actor : actors) {        
        actor->tick();
    }

    int index = 0;
    for (const shared_ptr<Actor>& actor : actors) {
        if (index < 256) 
            glStencilFunc(GL_ALWAYS, index, 0xFF);
        index++;
        
        actor->draw();
    }
    
    glfwPollEvents();
    glfwSwapBuffers(Screen::getInstance()->getWindow());
}

void Scene::addActor(const shared_ptr<Actor>& actor) {
    actors.push_back(actor);
}

void Scene::removeActor(const shared_ptr<Actor>& actor) {
    int index = std::distance(actors.begin(), std::find_if(actors.begin(), actors.end(), [&](std::shared_ptr<Actor> a) { return a.get() == actor.get(); }));
    actors.erase(actors.begin() + index);
}

void Scene::addLight(const shared_ptr<Light>& light) {
    lights.push_back(light);
    light->addOnLightChangeListener(this);
}

void Scene::removeLight(const shared_ptr<Light>& light) {
    int index = std::distance(lights.begin(), std::find_if(lights.begin(), lights.end(), [&](std::shared_ptr<Light> l) { return l.get() == light.get(); }));
    lights.erase(lights.begin() + index);
    //TODO: create notify for allLights
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

void Scene::setSkybox(shared_ptr<Actor> skybox) {
    glActiveTexture(GL_TEXTURE0);
    this->skybox = skybox;
}

vector<shared_ptr<Light>> Scene::getLights() {
    return this->lights;
}

shared_ptr<Actor> Scene::getActor(int index) {
    if (index >= actors.size() || index < 0) return nullptr;
    return actors[index];
}

shared_ptr<Light> Scene::getLight(int index) {
    if (index >= lights.size() || index < 0) return nullptr;
    return lights[index];
}
