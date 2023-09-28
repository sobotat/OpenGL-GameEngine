#include "Mesh.h"

#include <cstddef>
#include <utility>
#include <GL/glew.h>

Mesh::Mesh(vector<float> meshPoints) {
    points = move(meshPoints);
        
    //vertex buffer object (VBO)
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //created array of points from vector
    float* pointsArray = new float[points.size()];
    copy(points.begin(), points.end(), pointsArray);
    
    glBufferData(GL_ARRAY_BUFFER, points.size(), pointsArray, GL_STATIC_DRAW);
	
    //Vertex Array Object (VAO
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, points.size(), GL_FLOAT, GL_FALSE, 0, NULL);
}

void Mesh::tick() {}

void Mesh::draw() {
    glBindVertexArray(VAO);        
    glDrawArrays(GL_TRIANGLES, 0, points.size()); //mode,first,count
}

bool operator==(const Mesh& mesh1, const Mesh& mesh2) {
    return mesh1.VAO == mesh2.VAO;
}
