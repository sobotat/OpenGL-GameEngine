#include "Mesh.h"

#include <cstddef>
#include <utility>
#include <GL/glew.h>

void Mesh::setPoints(vector<float> meshPoints) {
    points = std::move(meshPoints);
        
    //vertex buffer object (VBO)
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float) * 3, &points.front(), GL_STATIC_DRAW);
	
    //Vertex Array Object (VAO
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Mesh::tick() {}

void Mesh::draw() {
    glBindVertexArray(VAO);        
    glDrawArrays(GL_TRIANGLES, 0, points.size()); //mode,first,count
}

bool operator==(const Mesh& mesh1, const Mesh& mesh2) {
    return mesh1.VAO == mesh2.VAO;
}
