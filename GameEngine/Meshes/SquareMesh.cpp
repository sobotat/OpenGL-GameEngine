#include "SquareMesh.h"

SquareMesh::SquareMesh() : Mesh() {
    setPoints({
        -0.8f, 0.2f, 0.0f,
        -0.8f, -0.2f, 0.0f,
        -0.4f, 0.2f, 0.0f,
        -0.4f, 0.2f, 0.0f,
        -0.4f, -0.2f, 0.0f,
        -0.8f, -0.2f, 0.0f,
    });
}
