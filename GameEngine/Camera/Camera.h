#pragma once
#include <glm/ext/matrix_float4x4.hpp>

#include "CameraListener.hpp"
#include "../ScreenListener.hpp"
#include "../Inputs/Input.h"
#include "../Lights/SpotLight.h"

using namespace std;
using namespace glm;

class CameraListener;

class Camera :
    public ScreenListener,
    public OnKeyListener,
    public OnCursorListener,
    public enable_shared_from_this<Camera> {

    vector<CameraListener*> listeners;
    shared_ptr<SpotLight> light;
    
    float fov;
    float cursorSpeed = 0.1f;
    float moveSpeed = 0.1f;

    mat4 projectionMatrix = mat4(1);
    vec3 position, target, up;

    double pitch = -90.0f;
    double yaw = -90.0f;
    double lastX, lastY;

    void notifyOnCameraChanged();
    
public:
    Camera();
    mat4 getView();
    mat4 getProjection();
    vec3 getPosition();

    double getLastX();
    double getLastY();

    void addListenerOnCameraChanged(CameraListener* listener);
    void attachLight(shared_ptr<SpotLight> light);

    void onScreenChanged(Screen* screen) override;
    void onKeyChanged(KeyInput keyInput) override;
    void onCursorChanged(CursorInput cursorInput) override;
};
