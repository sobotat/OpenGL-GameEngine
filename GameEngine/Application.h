
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
    vector<shared_ptr<Shader>> shaders;
    map<string, shared_ptr<Mesh>> meshes;
    vector<shared_ptr<Scene>> scenes;

    vector<ActiveSceneListener*> activeSceneListeners;

    int activeScene = 0;
    shared_ptr<Camera> camera = nullptr;
    shared_ptr<TransformKeyListener> transformKeyListener;

    void onExit();
    void loadSceneA(shared_ptr<Mesh> plane, shared_ptr<Mesh> mesh);
    void loadSceneB(shared_ptr<Mesh> plane, shared_ptr<Mesh> mesh);
    void loadSceneC(shared_ptr<Mesh> plane, shared_ptr<Mesh> mesh1, shared_ptr<Mesh> mesh2, shared_ptr<Mesh> mesh3);

    void notifyActiveSceneChanged();
    
public:
    ~Application();
    static shared_ptr<Application> getInstance();
    void init();
    void createShaders();
    void createModels();
    void createScenes();
    void run();

    shared_ptr<Scene> getScene();    
    shared_ptr<Camera> getCamera();

    void onKeyChanged(KeyInput keyInput) override;

    void addOnActiveSceneChanged(ActiveSceneListener* listener);
};
