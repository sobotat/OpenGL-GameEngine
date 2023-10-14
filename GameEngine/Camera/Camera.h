#pragma once
#include <glm/ext/matrix_float4x4.hpp>

#include "CameraListener.hpp"
#include "../ScreenListener.hpp"
#include "../Inputs/Input.h"

using namespace std;
using namespace glm;

class CameraListener;

class Camera :
    public ScreenListener,
    public OnKeyListener,
    public OnCursorListener {

    vector<CameraListener*> listeners;
    
    float fov;
    float cursorSpeed = 0.005f;
    float moveSpeed = 0.025f;

    mat4 projectionMatrix = mat4(1);
    vec3 position, target, up;

    void notifyOnCameraChanged();
    
public:
    Camera();
    mat4 getView();
    mat4 getProjection();

    void addListenerOnCameraChanged(CameraListener* listener);

    void onScreenChanged(Screen* screen) override;
    void onKeyChanged(KeyInput keyInput) override;
    void onCursorChanged(CursorInput cursorInput) override;
};
