#include "Scene.h"

#include <GLFW/glfw3.h>

#include "Aplication.h"

void Scene::draw() {
    // clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (Mesh* mesh : meshes) {
        mesh->draw();
    }

    // update other events like input handling
    glfwPollEvents();
    // put the stuff we’ve been drawing onto the display
    glfwSwapBuffers(Aplication::getInstance()->getWindow());
}

void Scene::addMesh(Mesh* mesh) {
    meshes.push_back(mesh);
}

void Scene::destroyMesh(Mesh* mesh) {
    meshes.erase(remove(meshes.begin(), meshes.end(), mesh), meshes.end());
}
