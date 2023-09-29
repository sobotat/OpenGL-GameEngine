#pragma once
#include <GL/glew.h>
#include <vector>

#include "Shader.h"

using namespace std;
class ShaderProgram {
protected:
    GLuint program;
    vector<Shader*> shaders; 
    
public:
    ShaderProgram(vector<Shader*> shaders);
    ~ShaderProgram();
    void useProgram();
};
