#include "CubeMesh.h"
#include "Meshes/MeshData/SkyCube.hpp"

CubeMesh::CubeMesh() : Mesh() {    
    setPoints(skycube);
}

void CubeMesh::setPoints(vector<float> meshPoints) {
    points = meshPoints;
    
    //vertex buffer object (VBO)
    glGenBuffers(1, &VBO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), &points.front(), GL_STATIC_DRAW);
	
    //Vertex Array Object (VAO)
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    const int sizeOf0 = 3 * sizeof(float);    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeOf0, (GLvoid*) 0);
}
