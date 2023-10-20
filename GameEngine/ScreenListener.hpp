#pragma once
#include "Screen.h"

using namespace std;
class Screen;

class ScreenListener {
public:
    virtual ~ScreenListener() = default;
    virtual void onScreenChanged(Screen* screen) = 0;
};
