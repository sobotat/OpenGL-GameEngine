#pragma once
#include "../Input.h"

class TransformKeyListener : public OnKeyListener{
protected:
    int selectedIndex = 0;
    char mode = 'L';

    void onLeft();
    void onRight();
    void onUp();
    void onDown();
    
public:
    void onKeyChanged(KeyInput keyInput) override;
};
