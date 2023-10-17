#pragma once
#include "../Input.h"

class TransformKeyListener : public OnKeyListener{
protected:
    int selectedIndex = 0;
    char mode = 'L';

    void onLeft() const;
    void onRight() const;
    void onUp() const;
    void onDown() const;
    
public:
    void onKeyChanged(KeyInput keyInput) override;
};
