#pragma once
#include "Camera.h"

class Camera;

class CameraListener {
public:
    virtual ~CameraListener() = default;
    virtual void onCameraChanged(Camera* camera) = 0;
};
