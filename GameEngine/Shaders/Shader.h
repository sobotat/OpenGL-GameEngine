#pragma once
#include <string>
#include <GL/glew.h>
#include "../Utils/UtilClass.h"

using namespace std;
class Shader {
    
protected:
    string source;
    GLuint shader;
    bool isCompiled = false;

    bool checkCompile();

public:
    virtual ~Shader() = default;
    virtual void compile();
    virtual void attach(GLuint shaderProgram);

    virtual string getName();
};
