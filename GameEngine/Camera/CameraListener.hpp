#pragma once
#include <memory>

#include "Camera.h"

class Camera;

using namespace std;
class CameraListener {
public:
    virtual ~CameraListener() = default;
    virtual void onCameraChanged(shared_ptr<Camera> camera) = 0;
};
