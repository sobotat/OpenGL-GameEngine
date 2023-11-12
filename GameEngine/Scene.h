#pragma once
#include <vector>
#include <memory>

#include "LightChangedInSceneListener.hpp"
#include "Actors/Actor.h"
#include "Lights/Light.h"

class Actor;
class LightChangedInSceneListener;

using namespace std;
class Scene : public LightListener, public enable_shared_from_this<Scene> {
protected:    
    vector<shared_ptr<Actor>> actors;
    vector<shared_ptr<Light>> lights;

    vector<shared_ptr<LightChangedInSceneListener>> lightListeners;
    void notifyLightChangedInSceneChanged(shared_ptr<Light> light);
    
    shared_ptr<Actor> skybox;
    
public:
    ~Scene();
    void draw();
    void addActor(const shared_ptr<Actor>& actor);
    void addLight(const shared_ptr<Light>& light);
    void removeLight(const shared_ptr<Light>& light);

    void onLightChanged(shared_ptr<Light> light) override;

    void addLightChangedInSceneChanged(shared_ptr<LightChangedInSceneListener> listener);
    void clearLightChangedInSceneChanged();
    void setSkybox(shared_ptr<Actor> skybox);

    vector<shared_ptr<Light>> getLights();
    shared_ptr<Actor> getActor(int index);
    shared_ptr<Light> getLight(int index);
};
