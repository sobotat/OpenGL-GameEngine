
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <map>

#include "Scene.h"
#include "Inputs/Listeners/TransformKeyListener.h"
#include "Shaders/ShaderProgram.h"
#include "ActiveSceneListener.hpp"

class Application :
    public OnKeyListener {
protected:
    static shared_ptr<Application> instance_;

    map<string, shared_ptr<ShaderProgram>> shaderPrograms;
    map<string, shared_ptr<Material>> materials;
    vector<shared_ptr<Shader>> shaders;
    map<string, shared_ptr<Mesh>> meshes;
    vector<shared_ptr<Scene>> scenes;

    vector<ActiveSceneListener*> activeSceneListeners;

    int activeScene = 0;
    shared_ptr<Camera> camera = nullptr;
    shared_ptr<SpotLight> cameraLight = nullptr;
    shared_ptr<TransformKeyListener> transformKeyListener;

    void onExit();
    void loadSceneA();
    void loadSceneB();
    void loadSceneC();
    void loadSceneD();
    void loadSceneE();
    void loadSceneF();

    void notifyActiveSceneChanged();
    
public:
    ~Application();
    static shared_ptr<Application> getInstance();
    void init();
    void createShaders();
    void createMaterials();
    void createModels();
    void createScenes();
    void run();

    shared_ptr<Scene> getScene();
    vector<shared_ptr<Scene>> getAllScenes();
    shared_ptr<Camera> getCamera();
    shared_ptr<Mesh> getMesh(string name);
    shared_ptr<ShaderProgram> getShaderProgram(string name);
    shared_ptr<Material> getMaterial(string name);

    void onKeyChanged(KeyInput keyInput) override;

    void addOnActiveSceneChanged(ActiveSceneListener* listener);
};

inline shared_ptr<Material> Application::getMaterial(string name) {
    return materials[name];
}
