#pragma once
#include <GL/glew.h>
#include <vector>

using namespace std;
class Mesh {
protected:
    vector<float> points;
    GLuint VBO = 0;
    GLuint VAO = 0;
    
public:
    virtual void setPoints(vector<float> meshPoints);
    virtual void tick();
    virtual void draw();

    friend bool operator==(const Mesh& mesh1, const Mesh& mesh2);
};
