#pragma once
#include <vector>
#include <memory>

#include "Actors/Actor.h"

using namespace std;
class Scene {
protected:
    vector<shared_ptr<Actor>> actors;
    
public:
    ~Scene();
    void draw();
    void addActor(const shared_ptr<Actor>& actor);
    shared_ptr<Actor> getActor(int index);
};
