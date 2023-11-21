#pragma once
#include <glm/common.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Inputs/Input.h"
using namespace glm;

struct SelectResult {
    bool found;
    int x;
    int y;
    unsigned int index;
    float depth;
    vec3 position;
    vec4 color;    
};

class OnSelectListener {
public:
    virtual ~OnSelectListener() = default;
    virtual void OnSelected(SelectResult result) = 0;
};

class SelectListener : public OnMouseListener, public OnCursorListener {
protected:
    vector<OnSelectListener*> listeners;
    
    int lastX = 0, lastY = 0;    
    GLbyte color[4] = {0, 0, 0, 0};
    GLfloat depth = 1;
    GLuint index = 0;
    vec3 position = vec3(0);

    void notifyOnSelected() const;
    
public:
    void onMouseChanged(MouseInput mouseInput) override;
    void onCursorChanged(CursorInput cursorInput) override;

    void addListenerOnSelected(OnSelectListener* listener);
};
