#pragma once

#include "Scene.h"
#include "Lights/Light.h"

class Scene;
class Light;

using namespace std;
class LightChangedInSceneListener {
public:
    virtual ~LightChangedInSceneListener() = default;
    virtual void onLightChangedInSceneChanged(shared_ptr<Scene> scene, shared_ptr<Light> light, int index) = 0;
};
