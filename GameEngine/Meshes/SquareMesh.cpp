#include "SquareMesh.h"

SquareMesh::SquareMesh(ShaderProgram* shaderProgram) : Mesh(shaderProgram) {    
    setPoints({
        { { -.5f, -.5f, .5f, 1 }, { 1, 1, 0, 1 } },
        { { -.5f,  .5f, .5f, 1 }, { 1, 0, 0, 1 } },
        { {  .5f,  .5f, .5f, 1 }, { 0, 0, 0, 1 } },
        { {  .5f, -.5f, .5f, 1 }, { 0, 1, 0, 1 } },
        { { -.5f, -.5f, .5f, 1 }, { 0, 0, 0, 1 } },
        { {  .5f,  .5f, .5f, 1 }, { 0, 0, 0, 1 } },
    });
}
