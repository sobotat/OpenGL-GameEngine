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
    public ActiveSceneListener {
protected:
    GLuint program;
    vector<shared_ptr<Shader>> shaders;

    mat4 viewMatrix = mat4(1);
    mat4 projectionMatrix = mat4(1);
    vec3 cameraPosition = vec3(1);
    
public:
    ShaderProgram(vector<shared_ptr<Shader>> shaders);
    ~ShaderProgram();
    
    void useProgram();
    static void resetProgram();
    
    void setPropertyMatrix(mat4 value, string property);
    void setPropertyVec3(vec3 value, string property);
    void setPropertyVec4(vec4 value, string property);

    void onCameraChanged(shared_ptr<Camera> camera) override;
    void onActiveSceneChanged(shared_ptr<Scene> scene) override;
};
