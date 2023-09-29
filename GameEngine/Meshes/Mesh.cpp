#include "Mesh.h"

#include <cstddef>
#include <utility>
#include <GL/glew.h>

Mesh::Mesh(ShaderProgram* shaderProgram) {
    this->shaderProgram = shaderProgram;
}

Mesh::~Mesh() {
    points.clear();
}

void Mesh::setPoints(vector<float> meshPoints) {
    points = std::move(meshPoints);
        
    //vertex buffer object (VBO)
    glGenBuffers(1, &VBO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), &points.front(), GL_STATIC_DRAW);
	
    //Vertex Array Object (VAO)
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Mesh::tick() {}

void Mesh::draw() {
    shaderProgram->useProgram();
    glBindVertexArray(VAO);        
    glDrawArrays(GL_TRIANGLES, 0, points.size());
}

bool operator==(const Mesh& mesh1, const Mesh& mesh2) {
    return mesh1.VAO == mesh2.VAO;
}
