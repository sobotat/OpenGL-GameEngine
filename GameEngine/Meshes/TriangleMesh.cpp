#include "TriangleMesh.h"

TriangleMesh::TriangleMesh(ShaderProgram* shaderProgram) : Mesh(shaderProgram) {
    setPoints({
        0.0f, 0.2f, 0.0f,
        0.2f, -0.2f, 0.0f,
       -0.2f, -0.2f, 0.0f
    });
}
