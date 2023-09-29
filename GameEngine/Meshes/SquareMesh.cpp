#include "SquareMesh.h"

SquareMesh::SquareMesh(ShaderProgram* shaderProgram) : Mesh(shaderProgram) {
    setPoints({
        -0.4f, 0.4f, 0.0f,
        -0.4f, -0.4f, 0.0f,
         0.4f, 0.4f, 0.0f,
         0.4f, 0.4f, 0.0f,
         0.4f, -0.4f, 0.0f,
        -0.4f, -0.4f, 0.0f,
    });
}
