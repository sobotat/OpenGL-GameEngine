#pragma once
#include "../Input.h"

class TestKeyListener : public OnKeyListener{
public:
    void notify(KeyInput keyInput) override;
};
