#pragma once
#include <string>
#include <GL/glew.h>

using namespace std;
class Shader {
    
protected:
    string source;
    GLuint shader;
    bool isCompiled = false;

public:
    virtual void compile();
    virtual void attach(GLuint shaderProgram); 
};
