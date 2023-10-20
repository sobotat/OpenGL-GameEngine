#pragma once
#include <vector>
#include <memory>

#include "Actors/Actor.h"
#include "Lights/Light.h"

class Actor;

using namespace std;
class Scene {
protected:
    vector<shared_ptr<Actor>> actors;
    vector<shared_ptr<Light>> lights;
    
public:
    ~Scene();
    void draw();
    void addActor(const shared_ptr<Actor>& actor);
    void addLight(const shared_ptr<Light>& light);

    vector<shared_ptr<Light>> getLights();
    shared_ptr<Actor> getActor(int index);
};
