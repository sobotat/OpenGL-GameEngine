#pragma once
#include "Screen.h"

using namespace std;
class Screen;

class ScreenListener {
public:
    virtual ~ScreenListener() = default;
    virtual void onScreenChanged(shared_ptr<Screen> screen) = 0;
};
