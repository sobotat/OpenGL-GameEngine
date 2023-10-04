#pragma once
#include <GL/glew.h>
#include <vector>

#include "../Shaders/ShaderProgram.h"

using namespace std;
class Mesh {
protected:
    vector<float> points;
    int pointCount = 0;
    GLuint VBO = 0;
    GLuint VAO = 0;
    
public:
    virtual ~Mesh();
    virtual void setPoints(vector<vector<vector<float>>> meshPoints);
    virtual void draw();
};
