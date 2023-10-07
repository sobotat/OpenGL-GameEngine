#pragma once
#include <vector>

#include "Actors/Actor.h"

using namespace std;
class Scene {
protected:
    vector<Actor*> actors;
    
public:
    ~Scene();
    void draw();
    void addActor(Actor* actor);
};
