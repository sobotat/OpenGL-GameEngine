#pragma once

#include "Scene.h"

class Scene;

class ActiveSceneListener {
public:
    virtual ~ActiveSceneListener() = default;
    virtual void onActiveSceneChanged(shared_ptr<Scene> scene) = 0;
};
