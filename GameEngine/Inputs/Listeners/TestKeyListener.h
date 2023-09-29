#pragma once
#include "../Input.h"

class TestKeyListener : public OnKeyListener{
public:
    void onKeyChanged(KeyInput keyInput) override;
};
