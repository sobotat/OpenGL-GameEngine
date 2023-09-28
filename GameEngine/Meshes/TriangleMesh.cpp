#include "TriangleMesh.h"

TriangleMesh::TriangleMesh() : Mesh() {
    setPoints({
        0.0f, 0.2f, 0.0f,
        0.2f, -0.2f, 0.0f,
       -0.2f, -0.2f, 0.0f
    });
}
