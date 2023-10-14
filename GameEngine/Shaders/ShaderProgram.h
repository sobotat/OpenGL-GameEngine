#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm/ext/matrix_float4x4.hpp>

#include "Shader.h"
#include "../Camera/CameraListener.hpp"

using namespace std;
using namespace glm;

class ShaderProgram : public CameraListener{
protected:
    GLuint program;
    vector<Shader*> shaders;

    mat4 viewMatrix = mat4(1);
    mat4 projectionMatrix = mat4(1);
    
public:
    ShaderProgram(vector<Shader*> shaders);
    ~ShaderProgram();
    
    void useProgram();
    static void resetProgram();
    
    void setPropertyMatrix(mat4 value, string property);

    void onCameraChanged(Camera* camera) override;    
};
