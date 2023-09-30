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
    ShaderProgram* shaderProgram = nullptr;
    
public:
    Mesh(ShaderProgram* shaderProgram);
    virtual ~Mesh();
    virtual void setPoints(vector<vector<vector<float>>> meshPoints);
    virtual void tick();
    virtual void draw();

    friend bool operator==(const Mesh& mesh1, const Mesh& mesh2);
};
