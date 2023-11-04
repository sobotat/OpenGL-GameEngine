#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm/ext/matrix_float4x4.hpp>

#include "Shader.h"
#include "../ActiveSceneListener.hpp"
#include "../Camera/CameraListener.hpp"

class ActiveSceneListener;

using namespace std;
using namespace glm;

class ShaderProgram :
    public CameraListener,
    public ActiveSceneListener,
    public LightChangedInSceneListener {
protected:
    GLuint program;
    vector<shared_ptr<Shader>> shaders;
    
public:
    ShaderProgram(vector<shared_ptr<Shader>> shaders);
    ~ShaderProgram();
    
    void useProgram();
    static void resetProgram();
    
    void setProperty(mat4 value, string property);
    void setProperty(vec3 value, string property);
    void setProperty(vec4 value, string property);
    void setProperty(float value, string property);
    void setProperty(int value, string property);

    void onCameraChanged(shared_ptr<Camera> camera) override;
    void onActiveSceneChanged(shared_ptr<Scene> scene) override;
    void onLightChangedInSceneChanged(shared_ptr<Scene> scene, shared_ptr<Light> light, int index) override;
};
