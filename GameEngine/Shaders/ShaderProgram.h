#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm/ext/matrix_float4x4.hpp>

#include "Shader.h"

using namespace std;
using namespace glm;

class ShaderProgram {
protected:
    GLuint program;
    vector<Shader*> shaders; 
    
public:
    ShaderProgram(vector<Shader*> shaders);
    ~ShaderProgram();
    
    void useProgram();
    static void resetProgram();
    
    void setPropertyMatrix(mat4 value, string property);    
    
};
