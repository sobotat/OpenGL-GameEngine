#include "TriangleMesh.h"

TriangleMesh::TriangleMesh(ShaderProgram* shaderProgram) : Mesh(shaderProgram) {
    setPoints({
        { { -.3f, -.3f, .5f, 1 }, { 1, 1, 0, 1 } },
        { { 0.0f,  .3f, .5f, 1 }, { 1, 0, 0, 1 } },
        { {  .3f, -.3f, .5f, 1 }, { 0, 0, 0, 1 } },
    });
}
